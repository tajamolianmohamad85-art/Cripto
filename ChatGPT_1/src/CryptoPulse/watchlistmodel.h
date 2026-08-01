#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QVariantList>

class WatchlistModel final : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        SymbolRole = Qt::UserRole + 1,
        NameRole,
        CoinIdRole,
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
    };

    struct Coin {
        QString symbol;
        QString name;
        QString coinId;
        double price = 0.0;
        double change = 0.0;
        double changeOneHour = 0.0;
        double changeSevenDays = 0.0;
        double marketCap = 0.0;
        double volume = 0.0;
        double high = 0.0;
        double low = 0.0;
        int rank = 0;
        QVariantList sparkline;
        bool hasPrice = false;
        int direction = 0;
    };

    explicit WatchlistModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool contains(const QString &symbol) const;
    bool addCoin(const QString &symbol, const QString &name, const QString &coinId, int rank = 0);
    bool removeCoin(const QString &symbol);
    void updateMarket(
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
        const QVariantList &sparkline);

    Coin coinForSymbol(const QString &symbol) const;
    QStringList coinIds() const;
    QString firstSymbol() const;

private:
    int indexOfSymbol(const QString &symbol) const;
    int indexOfCoinId(const QString &coinId) const;

    QList<Coin> m_coins;
};
