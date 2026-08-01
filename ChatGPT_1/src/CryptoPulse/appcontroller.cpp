#include "appcontroller.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPointF>
#include <QUrlQuery>
#include <QtMath>

#include <algorithm>
#include <limits>

namespace {
constexpr auto CoinGeckoBase = "https://api.coingecko.com/api/v3/";
constexpr int NetworkTimeoutMilliseconds = 15000;
constexpr int RefreshIntervalMilliseconds = 30000;
constexpr int ChartCacheSeconds = 300;
constexpr int MaximumChartPoints = 480;

const QList<AppController::ConnectionState> transientStates = {
    AppController::Starting,
    AppController::Connecting,
    AppController::Reconnecting
};
}

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    // QML_ELEMENT with qt_add_qml_module is compile-time visible to QML tooling
    // and avoids fragile runtime context-property registration.
    seedDefaults();

    m_refreshTimer.setInterval(RefreshIntervalMilliseconds);
    connect(&m_refreshTimer, &QTimer::timeout, this, &AppController::fetchQuotes);

    m_retryTimer.setSingleShot(true);
    connect(&m_retryTimer, &QTimer::timeout, this, &AppController::fetchQuotes);

    fetchCatalog();
    fetchQuotes();
    selectCoin(QStringLiteral("BTC"));
}

QAbstractItemModel *AppController::watchlistModel()
{
    return &m_watchlist;
}

AppController::ConnectionState AppController::connectionState() const
{
    return m_connectionState;
}

QString AppController::connectionText() const
{
    switch (m_connectionState) {
    case Starting:
        return QStringLiteral("Starting");
    case Connecting:
        return QStringLiteral("Updating");
    case Live:
        return QStringLiteral("Live · 30s");
    case Reconnecting:
        return QStringLiteral("Retrying");
    case Offline:
        return QStringLiteral("Offline");
    }
    return {};
}

QDateTime AppController::lastUpdated() const
{
    return m_lastUpdated;
}

QString AppController::notice() const
{
    return m_notice;
}

bool AppController::noticeIsError() const
{
    return m_noticeIsError;
}

QString AppController::selectedSymbol() const
{
    return m_selectedSymbol;
}

QString AppController::selectedName() const
{
    return m_selectedName;
}

double AppController::selectedPrice() const
{
    return m_selectedPrice;
}

double AppController::selectedChange() const
{
    return m_selectedChange;
}

double AppController::selectedChangeOneHour() const
{
    return m_selectedChangeOneHour;
}

double AppController::selectedChangeSevenDays() const
{
    return m_selectedChangeSevenDays;
}

double AppController::selectedMarketCap() const
{
    return m_selectedMarketCap;
}

double AppController::selectedVolume() const
{
    return m_selectedVolume;
}

double AppController::selectedHigh() const
{
    return m_selectedHigh;
}

double AppController::selectedLow() const
{
    return m_selectedLow;
}

int AppController::selectedRank() const
{
    return m_selectedRank;
}

bool AppController::selectedHasPrice() const
{
    return m_selectedHasPrice;
}

QString AppController::chartRange() const
{
    return m_chartRange;
}

QString AppController::chartRangeLabel() const
{
    if (m_chartRange == QStringLiteral("1D"))
        return QStringLiteral("24 hour");
    if (m_chartRange == QStringLiteral("7D"))
        return QStringLiteral("7 day");
    if (m_chartRange == QStringLiteral("30D"))
        return QStringLiteral("30 day");
    return QStringLiteral("1 year");
}

QVariantList AppController::chartPoints() const
{
    return m_chartPoints;
}

double AppController::chartMinimum() const
{
    return m_chartMinimum;
}

double AppController::chartMaximum() const
{
    return m_chartMaximum;
}

double AppController::chartPeriodChange() const
{
    return m_chartPeriodChange;
}

double AppController::chartHigh() const
{
    return m_chartHigh;
}

double AppController::chartLow() const
{
    return m_chartLow;
}

QString AppController::chartStartLabel() const
{
    return m_chartStartLabel;
}

QString AppController::chartMiddleLabel() const
{
    return m_chartMiddleLabel;
}

QString AppController::chartEndLabel() const
{
    return m_chartEndLabel;
}

bool AppController::chartLoading() const
{
    return m_chartLoading;
}

QString AppController::chartError() const
{
    return m_chartError;
}

bool AppController::addCoin(const QString &input)
{
    const QString symbol = input.trimmed().toUpper();
    if (symbol.isEmpty()) {
        setNotice(QStringLiteral("Enter a cryptocurrency symbol."), true);
        return false;
    }
    if (symbol.size() > 15) {
        setNotice(QStringLiteral("That symbol is not valid."), true);
        return false;
    }
    if (m_watchlist.contains(symbol)) {
        setNotice(symbol + QStringLiteral(" is already in the watchlist."), true);
        return false;
    }
    if (!m_catalogReady) {
        setNotice(QStringLiteral("The top-market catalog is still loading. Try again shortly."), true);
        fetchCatalog();
        return false;
    }

    const auto marketIt = m_markets.constFind(symbol);
    if (marketIt == m_markets.cend()) {
        setNotice(
            QStringLiteral("%1 was not found in CoinGecko's top 250 USD markets.").arg(symbol),
            true);
        return false;
    }

    const Market market = marketIt.value();
    m_watchlist.addCoin(market.symbol, market.name, market.coinId, market.rank);
    setNotice(market.name + QStringLiteral(" added to the watchlist."), false);
    fetchQuotes();
    selectCoin(market.symbol);
    return true;
}

void AppController::removeCoin(const QString &symbol)
{
    const WatchlistModel::Coin coin = m_watchlist.coinForSymbol(symbol);
    if (coin.symbol.isEmpty())
        return;

    m_watchlist.removeCoin(symbol);
    if (m_selectedSymbol != symbol)
        return;

    cancelChartRequest();
    const QString nextSymbol = m_watchlist.firstSymbol();
    if (!nextSymbol.isEmpty()) {
        selectCoin(nextSymbol);
        return;
    }

    m_selectedSymbol.clear();
    m_selectedName.clear();
    m_selectedCoinId.clear();
    m_selectedPrice = 0.0;
    m_selectedChange = 0.0;
    m_selectedChangeOneHour = 0.0;
    m_selectedChangeSevenDays = 0.0;
    m_selectedMarketCap = 0.0;
    m_selectedVolume = 0.0;
    m_selectedHigh = 0.0;
    m_selectedLow = 0.0;
    m_selectedRank = 0;
    m_selectedHasPrice = false;
    m_chartPoints.clear();
    m_chartTimes.clear();
    emit selectedCoinChanged();
    emit chartPointsChanged();
}

void AppController::selectCoin(const QString &symbol)
{
    const WatchlistModel::Coin coin = m_watchlist.coinForSymbol(symbol);
    if (coin.symbol.isEmpty())
        return;

    if (m_selectedSymbol == coin.symbol) {
        updateSelectedMarket(coin);
        if (m_chartLoading || !m_chartPoints.isEmpty())
            return;
    } else {
        applySelectedCoin(coin);
    }

    requestChart();
}

void AppController::setChartRange(const QString &range)
{
    static const QStringList ranges = {
        QStringLiteral("1D"),
        QStringLiteral("7D"),
        QStringLiteral("30D"),
        QStringLiteral("1Y")
    };
    if (!ranges.contains(range) || range == m_chartRange)
        return;

    m_chartRange = range;
    emit chartRangeChanged();
    requestChart();
}

void AppController::refresh()
{
    dismissNotice();
    fetchQuotes();
}

void AppController::retryConnections()
{
    dismissNotice();
    m_retryTimer.stop();
    m_retryAttempt = 0;
    if (!m_catalogReady)
        fetchCatalog();
    fetchQuotes();
    if (!m_chartError.isEmpty())
        requestChart(true);
}

void AppController::dismissNotice()
{
    if (m_notice.isEmpty())
        return;
    m_notice.clear();
    m_noticeIsError = false;
    emit noticeChanged();
}

QString AppController::formatPrice(double value) const
{
    if (!qIsFinite(value))
        return QStringLiteral("—");

    int decimals = 2;
    if (value < 0.01)
        decimals = 6;
    else if (value < 1.0)
        decimals = 4;

    return QLocale(QLocale::English, QLocale::UnitedStates).toString(value, 'f', decimals);
}

QString AppController::formatChange(double value) const
{
    if (!qIsFinite(value))
        return QStringLiteral("—");
    return QStringLiteral("%1%2%")
        .arg(value >= 0.0 ? QStringLiteral("+") : QString{})
        .arg(value, 0, 'f', 2);
}

QString AppController::formatCompactNumber(double value) const
{
    if (!qIsFinite(value) || value <= 0.0)
        return QStringLiteral("—");

    static const QList<QPair<double, QString>> units = {
        {1.0e12, QStringLiteral("T")},
        {1.0e9, QStringLiteral("B")},
        {1.0e6, QStringLiteral("M")},
        {1.0e3, QStringLiteral("K")}
    };
    for (const auto &[divisor, suffix] : units) {
        if (value >= divisor)
            return QStringLiteral("$%1%2").arg(value / divisor, 0, 'f', 2).arg(suffix);
    }
    return QStringLiteral("$%1").arg(formatPrice(value));
}

QVariantMap AppController::chartPointInfo(int index) const
{
    if (m_chartPoints.isEmpty() || m_chartTimes.isEmpty())
        return {};

    const int safeIndex = std::clamp(index, 0, int(m_chartPoints.size()) - 1);
    const double price = m_chartPoints.at(safeIndex).toPointF().y();
    const double firstPrice = m_chartPoints.constFirst().toPointF().y();
    const double change = firstPrice > 0.0 ? ((price / firstPrice) - 1.0) * 100.0 : 0.0;
    const QDateTime time = QDateTime::fromMSecsSinceEpoch(m_chartTimes.at(safeIndex)).toLocalTime();
    const QString format = m_chartRange == QStringLiteral("1Y")
        ? QStringLiteral("MMM d, yyyy")
        : QStringLiteral("MMM d · HH:mm");

    return {
        {QStringLiteral("index"), safeIndex},
        {QStringLiteral("price"), price},
        {QStringLiteral("change"), change},
        {QStringLiteral("time"), time.toString(format)}
    };
}

void AppController::seedDefaults()
{
    const QList<Market> defaults = {
        {QStringLiteral("BTC"), QStringLiteral("Bitcoin"), QStringLiteral("bitcoin"), 1},
        {QStringLiteral("ETH"), QStringLiteral("Ethereum"), QStringLiteral("ethereum"), 2},
        {QStringLiteral("SOL"), QStringLiteral("Solana"), QStringLiteral("solana"), 6},
        {QStringLiteral("XRP"), QStringLiteral("XRP"), QStringLiteral("ripple"), 4},
        {QStringLiteral("ADA"), QStringLiteral("Cardano"), QStringLiteral("cardano"), 10}
    };

    for (const Market &market : defaults) {
        m_markets.insert(market.symbol, market);
        m_watchlist.addCoin(market.symbol, market.name, market.coinId, market.rank);
    }
}

void AppController::fetchCatalog()
{
    if (m_catalogReply)
        return;

    QUrl url(QString::fromLatin1(CoinGeckoBase) + QStringLiteral("coins/markets"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("vs_currency"), QStringLiteral("usd"));
    query.addQueryItem(QStringLiteral("order"), QStringLiteral("market_cap_desc"));
    query.addQueryItem(QStringLiteral("per_page"), QStringLiteral("250"));
    query.addQueryItem(QStringLiteral("page"), QStringLiteral("1"));
    query.addQueryItem(QStringLiteral("sparkline"), QStringLiteral("false"));
    url.setQuery(query);

    QNetworkReply *reply = m_network.get(makeRequest(url));
    m_catalogReply = reply;
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (m_catalogReply == reply)
            m_catalogReply = nullptr;
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError)
            return;

        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &parseError);
        if (parseError.error != QJsonParseError::NoError || !document.isArray())
            return;

        const QJsonArray markets = document.array();
        for (const QJsonValue &value : markets) {
            const QJsonObject object = value.toObject();
            const QString symbol = object.value(QStringLiteral("symbol")).toString().toUpper();
            const QString coinId = object.value(QStringLiteral("id")).toString();
            const QString name = object.value(QStringLiteral("name")).toString();
            const int rank = object.value(QStringLiteral("market_cap_rank")).toInt();
            if (!symbol.isEmpty() && !coinId.isEmpty() && !m_markets.contains(symbol))
                m_markets.insert(symbol, {symbol, name, coinId, rank});
        }
        m_catalogReady = true;
    });
}

void AppController::fetchQuotes()
{
    if (m_quotesReply || m_watchlist.coinIds().isEmpty())
        return;

    if (transientStates.contains(m_connectionState) || !m_lastUpdated.isValid())
        setConnectionState(Connecting);

    QUrl url(QString::fromLatin1(CoinGeckoBase) + QStringLiteral("coins/markets"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("vs_currency"), QStringLiteral("usd"));
    query.addQueryItem(QStringLiteral("ids"), m_watchlist.coinIds().join(QLatin1Char(',')));
    query.addQueryItem(QStringLiteral("order"), QStringLiteral("market_cap_desc"));
    query.addQueryItem(QStringLiteral("sparkline"), QStringLiteral("true"));
    query.addQueryItem(QStringLiteral("price_change_percentage"), QStringLiteral("1h,24h,7d"));
    query.addQueryItem(QStringLiteral("precision"), QStringLiteral("full"));
    url.setQuery(query);

    QNetworkReply *reply = m_network.get(makeRequest(url));
    m_quotesReply = reply;
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (m_quotesReply == reply)
            m_quotesReply = nullptr;
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            setNotice(networkErrorMessage(reply, QStringLiteral("refresh market prices")), true);
            scheduleQuoteRetry(reply);
            return;
        }

        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &parseError);
        if (parseError.error != QJsonParseError::NoError || !document.isArray()) {
            setNotice(QStringLiteral("CoinGecko returned invalid market data."), true);
            scheduleQuoteRetry(reply);
            return;
        }

        for (const QJsonValue &value : document.array()) {
            const QJsonObject object = value.toObject();
            const QString coinId = object.value(QStringLiteral("id")).toString();
            QVariantList sparkline;
            const QJsonArray sparklinePrices = object
                .value(QStringLiteral("sparkline_in_7d"))
                .toObject()
                .value(QStringLiteral("price"))
                .toArray();
            sparkline.reserve(sparklinePrices.size());
            for (const QJsonValue &sparkValue : sparklinePrices)
                sparkline.append(sparkValue.toDouble());

            m_watchlist.updateMarket(
                coinId,
                object.value(QStringLiteral("current_price")).toDouble(),
                object.value(QStringLiteral("price_change_percentage_24h")).toDouble(),
                object.value(QStringLiteral("price_change_percentage_1h_in_currency")).toDouble(),
                object.value(QStringLiteral("price_change_percentage_7d_in_currency")).toDouble(),
                object.value(QStringLiteral("market_cap")).toDouble(),
                object.value(QStringLiteral("total_volume")).toDouble(),
                object.value(QStringLiteral("high_24h")).toDouble(),
                object.value(QStringLiteral("low_24h")).toDouble(),
                object.value(QStringLiteral("market_cap_rank")).toInt(),
                sparkline);
        }

        const WatchlistModel::Coin selectedCoin = m_watchlist.coinForSymbol(m_selectedSymbol);
        if (!selectedCoin.symbol.isEmpty()) {
            updateSelectedMarket(selectedCoin);
            updateLiveChartPoint(selectedCoin.price);
        }

        m_retryAttempt = 0;
        m_retryTimer.stop();
        if (!m_refreshTimer.isActive())
            m_refreshTimer.start();
        m_lastUpdated = QDateTime::currentDateTime();
        setConnectionState(Live);
        emit lastUpdatedChanged();

        if (m_noticeIsError)
            dismissNotice();
    });
}

void AppController::scheduleQuoteRetry(QNetworkReply *reply)
{
    m_refreshTimer.stop();
    setConnectionState(Reconnecting);

    bool ok = false;
    const int retryAfterSeconds = reply->rawHeader("Retry-After").toInt(&ok);
    const int exponent = std::min(m_retryAttempt, 4);
    const int fallbackSeconds = std::min(60, 5 * (1 << exponent));
    ++m_retryAttempt;
    m_retryTimer.start((ok ? std::max(5, retryAfterSeconds) : fallbackSeconds) * 1000);
}

void AppController::requestChart(bool force)
{
    if (m_selectedCoinId.isEmpty())
        return;

    const QString cacheKey = chartCacheKey();
    const auto cached = m_chartCache.constFind(cacheKey);
    if (!force && cached != m_chartCache.cend()
        && cached->loadedAt.secsTo(QDateTime::currentDateTimeUtc()) < ChartCacheSeconds) {
        applyChartData(cached.value());
        return;
    }

    cancelChartRequest();
    setChartError({});
    setChartLoading(true);

    QUrl url(
        QString::fromLatin1(CoinGeckoBase)
        + QStringLiteral("coins/%1/market_chart").arg(m_selectedCoinId));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("vs_currency"), QStringLiteral("usd"));
    query.addQueryItem(QStringLiteral("days"), QString::number(chartDays()));
    query.addQueryItem(QStringLiteral("precision"), QStringLiteral("full"));
    url.setQuery(query);

    const QString requestedCoinId = m_selectedCoinId;
    const QString requestedRange = m_chartRange;
    QNetworkReply *reply = m_network.get(makeRequest(url));
    m_chartReply = reply;
    connect(reply, &QNetworkReply::finished, this, [this, reply, requestedCoinId, requestedRange] {
        if (m_chartReply == reply)
            m_chartReply = nullptr;
        reply->deleteLater();

        if (requestedCoinId != m_selectedCoinId || requestedRange != m_chartRange)
            return;

        setChartLoading(false);
        if (reply->error() != QNetworkReply::NoError) {
            if (reply->error() != QNetworkReply::OperationCanceledError)
                setChartError(networkErrorMessage(reply, QStringLiteral("load chart history")));
            return;
        }

        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &parseError);
        const QJsonArray prices = document.object().value(QStringLiteral("prices")).toArray();
        if (parseError.error != QJsonParseError::NoError || prices.size() < 2) {
            setChartError(QStringLiteral("Not enough recent market history is available."));
            return;
        }

        const int stride = std::max(1, qCeil(prices.size() / double(MaximumChartPoints)));
        ChartData data;
        data.points.reserve((prices.size() + stride - 1) / stride);
        data.times.reserve((prices.size() + stride - 1) / stride);
        for (int sourceIndex = 0; sourceIndex < prices.size(); sourceIndex += stride) {
            const QJsonArray point = prices.at(sourceIndex).toArray();
            if (point.size() < 2)
                continue;
            const qint64 timestamp = point.at(0).toInteger();
            const double price = point.at(1).toDouble();
            if (timestamp <= 0 || !qIsFinite(price) || price <= 0.0)
                continue;
            data.points.append(QVariant::fromValue(QPointF(data.points.size(), price)));
            data.times.append(timestamp);
        }

        if (data.points.size() < 2) {
            setChartError(QStringLiteral("Not enough recent market history is available."));
            return;
        }

        data.loadedAt = QDateTime::currentDateTimeUtc();
        m_chartCache.insert(chartCacheKey(), data);
        applyChartData(data);
    });
}

void AppController::cancelChartRequest()
{
    QNetworkReply *reply = m_chartReply;
    if (!reply)
        return;

    m_chartReply = nullptr;
    disconnect(reply, nullptr, this, nullptr);
    reply->abort();
    reply->deleteLater();
}

void AppController::applyChartData(const ChartData &data)
{
    m_chartPoints = data.points;
    m_chartTimes = data.times;
    setChartError({});
    setChartLoading(false);
    recalculateChartStats();

    const auto formatTime = [this](qint64 milliseconds) {
        const QDateTime time = QDateTime::fromMSecsSinceEpoch(milliseconds).toLocalTime();
        return m_chartRange == QStringLiteral("1Y")
            ? time.toString(QStringLiteral("MMM yyyy"))
            : time.toString(QStringLiteral("MMM d"));
    };
    m_chartStartLabel = formatTime(m_chartTimes.constFirst());
    m_chartMiddleLabel = formatTime(m_chartTimes.at(m_chartTimes.size() / 2));
    m_chartEndLabel = formatTime(m_chartTimes.constLast());

    emit chartPointsChanged();
    emit chartLabelsChanged();
}

void AppController::applySelectedCoin(const WatchlistModel::Coin &coin)
{
    m_selectedSymbol = coin.symbol;
    m_selectedName = coin.name;
    m_selectedCoinId = coin.coinId;
    updateSelectedMarket(coin);
}

void AppController::updateSelectedMarket(const WatchlistModel::Coin &coin)
{
    m_selectedPrice = coin.price;
    m_selectedChange = coin.change;
    m_selectedChangeOneHour = coin.changeOneHour;
    m_selectedChangeSevenDays = coin.changeSevenDays;
    m_selectedMarketCap = coin.marketCap;
    m_selectedVolume = coin.volume;
    m_selectedHigh = coin.high;
    m_selectedLow = coin.low;
    m_selectedRank = coin.rank;
    m_selectedHasPrice = coin.hasPrice;
    emit selectedCoinChanged();
}

void AppController::updateLiveChartPoint(double price)
{
    if (m_chartPoints.isEmpty() || !qIsFinite(price) || price <= 0.0)
        return;

    QPointF lastPoint = m_chartPoints.constLast().toPointF();
    if (qFuzzyCompare(lastPoint.y(), price))
        return;
    lastPoint.setY(price);
    m_chartPoints.last() = QVariant::fromValue(lastPoint);
    recalculateChartStats();
    emit chartPointsChanged();
}

void AppController::recalculateChartStats()
{
    if (m_chartPoints.isEmpty()) {
        m_chartMinimum = 0.0;
        m_chartMaximum = 1.0;
        m_chartPeriodChange = 0.0;
        m_chartHigh = 0.0;
        m_chartLow = 0.0;
        emit chartAxisRangeChanged();
        emit chartStatsChanged();
        return;
    }

    double minimum = std::numeric_limits<double>::max();
    double maximum = std::numeric_limits<double>::lowest();
    for (const QVariant &value : std::as_const(m_chartPoints)) {
        const double price = value.toPointF().y();
        minimum = std::min(minimum, price);
        maximum = std::max(maximum, price);
    }

    const double firstPrice = m_chartPoints.constFirst().toPointF().y();
    const double lastPrice = m_chartPoints.constLast().toPointF().y();
    const double span = maximum - minimum;
    const double padding = span > 0.0 ? span * 0.14 : maximum * 0.02;
    m_chartMinimum = std::max(0.0, minimum - padding);
    m_chartMaximum = maximum + padding;
    m_chartPeriodChange = firstPrice > 0.0 ? ((lastPrice / firstPrice) - 1.0) * 100.0 : 0.0;
    m_chartHigh = maximum;
    m_chartLow = minimum;
    emit chartAxisRangeChanged();
    emit chartStatsChanged();
}

void AppController::setConnectionState(ConnectionState state)
{
    if (m_connectionState == state)
        return;
    m_connectionState = state;
    emit connectionStateChanged();
}

void AppController::setNotice(const QString &message, bool error)
{
    if (m_notice == message && m_noticeIsError == error)
        return;
    m_notice = message;
    m_noticeIsError = error;
    emit noticeChanged();
}

void AppController::setChartLoading(bool loading)
{
    if (m_chartLoading == loading)
        return;
    m_chartLoading = loading;
    emit chartLoadingChanged();
}

void AppController::setChartError(const QString &error)
{
    if (m_chartError == error)
        return;
    m_chartError = error;
    emit chartErrorChanged();
}

int AppController::chartDays() const
{
    if (m_chartRange == QStringLiteral("1D"))
        return 1;
    if (m_chartRange == QStringLiteral("7D"))
        return 7;
    if (m_chartRange == QStringLiteral("30D"))
        return 30;
    return 365;
}

QString AppController::chartCacheKey() const
{
    return m_selectedCoinId + QLatin1Char('|') + m_chartRange;
}

QNetworkRequest AppController::makeRequest(const QUrl &url) const
{
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "CryptoPulse/2.0");
    request.setTransferTimeout(NetworkTimeoutMilliseconds);
    return request;
}

QString AppController::networkErrorMessage(QNetworkReply *reply, const QString &action) const
{
    const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status == 429)
        return QStringLiteral("CoinGecko rate-limited the request. Retrying automatically.");
    if (reply->error() == QNetworkReply::TimeoutError)
        return QStringLiteral("The network timed out while trying to %1.").arg(action);
    return QStringLiteral("Unable to %1: %2").arg(action, reply->errorString());
}
