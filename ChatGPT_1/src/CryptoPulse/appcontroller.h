#pragma once

#include "watchlistmodel.h"

#include <QAbstractItemModel>
#include <QDateTime>
#include <QHash>
#include <QNetworkAccessManager>
#include <QPointer>
#include <QQmlEngine>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

class QNetworkReply;

class AppController : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QAbstractItemModel *watchlistModel READ watchlistModel CONSTANT)
    Q_PROPERTY(ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString connectionText READ connectionText NOTIFY connectionStateChanged)
    Q_PROPERTY(QDateTime lastUpdated READ lastUpdated NOTIFY lastUpdatedChanged)
    Q_PROPERTY(QString notice READ notice NOTIFY noticeChanged)
    Q_PROPERTY(bool noticeIsError READ noticeIsError NOTIFY noticeChanged)
    Q_PROPERTY(QString selectedSymbol READ selectedSymbol NOTIFY selectedCoinChanged)
    Q_PROPERTY(QString selectedName READ selectedName NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedPrice READ selectedPrice NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedChange READ selectedChange NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedChangeOneHour READ selectedChangeOneHour NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedChangeSevenDays READ selectedChangeSevenDays NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedMarketCap READ selectedMarketCap NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedVolume READ selectedVolume NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedHigh READ selectedHigh NOTIFY selectedCoinChanged)
    Q_PROPERTY(double selectedLow READ selectedLow NOTIFY selectedCoinChanged)
    Q_PROPERTY(int selectedRank READ selectedRank NOTIFY selectedCoinChanged)
    Q_PROPERTY(bool selectedHasPrice READ selectedHasPrice NOTIFY selectedCoinChanged)
    Q_PROPERTY(QString chartRange READ chartRange NOTIFY chartRangeChanged)
    Q_PROPERTY(QString chartRangeLabel READ chartRangeLabel NOTIFY chartRangeChanged)
    Q_PROPERTY(QVariantList chartPoints READ chartPoints NOTIFY chartPointsChanged)
    Q_PROPERTY(double chartMinimum READ chartMinimum NOTIFY chartAxisRangeChanged)
    Q_PROPERTY(double chartMaximum READ chartMaximum NOTIFY chartAxisRangeChanged)
    Q_PROPERTY(double chartPeriodChange READ chartPeriodChange NOTIFY chartStatsChanged)
    Q_PROPERTY(double chartHigh READ chartHigh NOTIFY chartStatsChanged)
    Q_PROPERTY(double chartLow READ chartLow NOTIFY chartStatsChanged)
    Q_PROPERTY(QString chartStartLabel READ chartStartLabel NOTIFY chartLabelsChanged)
    Q_PROPERTY(QString chartMiddleLabel READ chartMiddleLabel NOTIFY chartLabelsChanged)
    Q_PROPERTY(QString chartEndLabel READ chartEndLabel NOTIFY chartLabelsChanged)
    Q_PROPERTY(bool chartLoading READ chartLoading NOTIFY chartLoadingChanged)
    Q_PROPERTY(QString chartError READ chartError NOTIFY chartErrorChanged)

public:
    enum ConnectionState {
        Starting,
        Connecting,
        Live,
        Reconnecting,
        Offline
    };
    Q_ENUM(ConnectionState)

    explicit AppController(QObject *parent = nullptr);

    QAbstractItemModel *watchlistModel();
    ConnectionState connectionState() const;
    QString connectionText() const;
    QDateTime lastUpdated() const;
    QString notice() const;
    bool noticeIsError() const;

    QString selectedSymbol() const;
    QString selectedName() const;
    double selectedPrice() const;
    double selectedChange() const;
    double selectedChangeOneHour() const;
    double selectedChangeSevenDays() const;
    double selectedMarketCap() const;
    double selectedVolume() const;
    double selectedHigh() const;
    double selectedLow() const;
    int selectedRank() const;
    bool selectedHasPrice() const;

    QString chartRange() const;
    QString chartRangeLabel() const;
    QVariantList chartPoints() const;
    double chartMinimum() const;
    double chartMaximum() const;
    double chartPeriodChange() const;
    double chartHigh() const;
    double chartLow() const;
    QString chartStartLabel() const;
    QString chartMiddleLabel() const;
    QString chartEndLabel() const;
    bool chartLoading() const;
    QString chartError() const;

    Q_INVOKABLE bool addCoin(const QString &input);
    Q_INVOKABLE void removeCoin(const QString &symbol);
    Q_INVOKABLE void selectCoin(const QString &symbol);
    Q_INVOKABLE void setChartRange(const QString &range);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void retryConnections();
    Q_INVOKABLE void dismissNotice();
    Q_INVOKABLE QString formatPrice(double value) const;
    Q_INVOKABLE QString formatChange(double value) const;
    Q_INVOKABLE QString formatCompactNumber(double value) const;
    Q_INVOKABLE QVariantMap chartPointInfo(int index) const;

signals:
    void connectionStateChanged();
    void lastUpdatedChanged();
    void noticeChanged();
    void selectedCoinChanged();
    void chartRangeChanged();
    void chartPointsChanged();
    void chartAxisRangeChanged();
    void chartStatsChanged();
    void chartLabelsChanged();
    void chartLoadingChanged();
    void chartErrorChanged();

private:
    struct Market {
        QString symbol;
        QString name;
        QString coinId;
        int rank = 0;
    };

    struct ChartData {
        QVariantList points;
        QList<qint64> times;
        QDateTime loadedAt;
    };

    void seedDefaults();
    void fetchCatalog();
    void fetchQuotes();
    void scheduleQuoteRetry(QNetworkReply *reply);
    void requestChart(bool force = false);
    void cancelChartRequest();
    void applyChartData(const ChartData &data);
    void applySelectedCoin(const WatchlistModel::Coin &coin);
    void updateSelectedMarket(const WatchlistModel::Coin &coin);
    void updateLiveChartPoint(double price);
    void recalculateChartStats();
    void setConnectionState(ConnectionState state);
    void setNotice(const QString &message, bool error);
    void setChartLoading(bool loading);
    void setChartError(const QString &error);
    int chartDays() const;
    QString chartCacheKey() const;
    QNetworkRequest makeRequest(const QUrl &url) const;
    QString networkErrorMessage(QNetworkReply *reply, const QString &action) const;

    WatchlistModel m_watchlist;
    QNetworkAccessManager m_network;
    QTimer m_refreshTimer;
    QTimer m_retryTimer;
    QPointer<QNetworkReply> m_catalogReply;
    QPointer<QNetworkReply> m_quotesReply;
    QPointer<QNetworkReply> m_chartReply;

    QHash<QString, Market> m_markets;
    QHash<QString, ChartData> m_chartCache;
    bool m_catalogReady = false;
    int m_retryAttempt = 0;
    ConnectionState m_connectionState = Starting;
    QDateTime m_lastUpdated;
    QString m_notice;
    bool m_noticeIsError = false;

    QString m_selectedSymbol;
    QString m_selectedName;
    QString m_selectedCoinId;
    double m_selectedPrice = 0.0;
    double m_selectedChange = 0.0;
    double m_selectedChangeOneHour = 0.0;
    double m_selectedChangeSevenDays = 0.0;
    double m_selectedMarketCap = 0.0;
    double m_selectedVolume = 0.0;
    double m_selectedHigh = 0.0;
    double m_selectedLow = 0.0;
    int m_selectedRank = 0;
    bool m_selectedHasPrice = false;

    QString m_chartRange = QStringLiteral("7D");
    QVariantList m_chartPoints;
    QList<qint64> m_chartTimes;
    double m_chartMinimum = 0.0;
    double m_chartMaximum = 1.0;
    double m_chartPeriodChange = 0.0;
    double m_chartHigh = 0.0;
    double m_chartLow = 0.0;
    QString m_chartStartLabel;
    QString m_chartMiddleLabel;
    QString m_chartEndLabel;
    bool m_chartLoading = false;
    QString m_chartError;
};
