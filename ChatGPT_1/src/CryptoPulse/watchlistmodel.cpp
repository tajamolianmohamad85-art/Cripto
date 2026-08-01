#include "watchlistmodel.h"

#include <QtMath>

WatchlistModel::WatchlistModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int WatchlistModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_coins.size();
}

QVariant WatchlistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_coins.size())
        return {};

    const Coin &coin = m_coins.at(index.row());
    switch (role) {
    case SymbolRole:
        return coin.symbol;
    case NameRole:
        return coin.name;
    case CoinIdRole:
        return coin.coinId;
    case PriceRole:
        return coin.price;
    case ChangeRole:
        return coin.change;
    case ChangeOneHourRole:
        return coin.changeOneHour;
    case ChangeSevenDaysRole:
        return coin.changeSevenDays;
    case MarketCapRole:
        return coin.marketCap;
    case VolumeRole:
        return coin.volume;
    case HighRole:
        return coin.high;
    case LowRole:
        return coin.low;
    case RankRole:
        return coin.rank;
    case SparklineRole:
        return coin.sparkline;
    case HasPriceRole:
        return coin.hasPrice;
    case DirectionRole:
        return coin.direction;
    default:
        return {};
    }
}

QHash<int, QByteArray> WatchlistModel::roleNames() const
{
    return {
        {SymbolRole, "symbol"},
        {NameRole, "name"},
        {CoinIdRole, "coinId"},
        {PriceRole, "price"},
        {ChangeRole, "change"},
        {ChangeOneHourRole, "changeOneHour"},
        {ChangeSevenDaysRole, "changeSevenDays"},
        {MarketCapRole, "marketCap"},
        {VolumeRole, "volume"},
        {HighRole, "high"},
        {LowRole, "low"},
        {RankRole, "rank"},
        {SparklineRole, "sparkline"},
        {HasPriceRole, "hasPrice"},
        {DirectionRole, "direction"}
    };
}

bool WatchlistModel::contains(const QString &symbol) const
{
    return indexOfSymbol(symbol) >= 0;
}

bool WatchlistModel::addCoin(
    const QString &symbol,
    const QString &name,
    const QString &coinId,
    int rank)
{
    if (contains(symbol) || coinId.isEmpty())
        return false;

    const int row = m_coins.size();
    beginInsertRows({}, row, row);
    Coin coin;
    coin.symbol = symbol;
    coin.name = name;
    coin.coinId = coinId;
    coin.rank = rank;
    m_coins.append(coin);
    endInsertRows();
    return true;
}

bool WatchlistModel::removeCoin(const QString &symbol)
{
    const int row = indexOfSymbol(symbol);
    if (row < 0)
        return false;

    beginRemoveRows({}, row, row);
    m_coins.removeAt(row);
    endRemoveRows();
    return true;
}

void WatchlistModel::updateMarket(
    const QString &coinId,
    double price,
    double change,
    double changeOneHour,
    double changeSevenDays,
    double marketCap,
    double volume,
    double high,
    double low,
    int rank,
    const QVariantList &sparkline)
{
    const int row = indexOfCoinId(coinId);
    if (row < 0 || !qIsFinite(price) || price <= 0.0)
        return;

    Coin &coin = m_coins[row];
    int direction = 0;
    if (coin.hasPrice) {
        if (price > coin.price)
            direction = 1;
        else if (price < coin.price)
            direction = -1;
    }

    coin.price = price;
    coin.change = change;
    coin.changeOneHour = changeOneHour;
    coin.changeSevenDays = changeSevenDays;
    coin.marketCap = marketCap;
    coin.volume = volume;
    coin.high = high;
    coin.low = low;
    coin.rank = rank;
    coin.sparkline = sparkline;
    coin.hasPrice = true;
    coin.direction = direction;

    const QModelIndex modelIndex = index(row);
    emit dataChanged(
        modelIndex,
        modelIndex,
        {
            PriceRole,
            ChangeRole,
            ChangeOneHourRole,
            ChangeSevenDaysRole,
            MarketCapRole,
            VolumeRole,
            HighRole,
            LowRole,
            RankRole,
            SparklineRole,
            HasPriceRole,
            DirectionRole
        });
}

WatchlistModel::Coin WatchlistModel::coinForSymbol(const QString &symbol) const
{
    const int row = indexOfSymbol(symbol);
    return row >= 0 ? m_coins.at(row) : Coin{};
}

QStringList WatchlistModel::coinIds() const
{
    QStringList result;
    result.reserve(m_coins.size());
    for (const Coin &coin : m_coins)
        result.append(coin.coinId);
    return result;
}

QString WatchlistModel::firstSymbol() const
{
    return m_coins.isEmpty() ? QString{} : m_coins.constFirst().symbol;
}

int WatchlistModel::indexOfSymbol(const QString &symbol) const
{
    for (int index = 0; index < m_coins.size(); ++index) {
        if (m_coins.at(index).symbol == symbol)
            return index;
    }
    return -1;
}

int WatchlistModel::indexOfCoinId(const QString &coinId) const
{
    for (int index = 0; index < m_coins.size(); ++index) {
        if (m_coins.at(index).coinId == coinId)
            return index;
    }
    return -1;
}
