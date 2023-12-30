#ifndef TRANSPORTDBSERVICE_H
#define TRANSPORTDBSERVICE_H

#include <QSharedPointer>
#include "ilocaldbservicebase.h"
#include "../Providers/localbbstorage.h"

class TransportDBProvider;
struct TransportData;

class TransportDBService : public ILocalDBServiceBase
{
    Q_OBJECT
public:
    explicit TransportDBService(QObject *parent = nullptr);

    // ILocalDBServiceBase interface
    quint64 tableSize() const override;
    QSqlError addEntry(QVariantMap &values) override;
    QSqlError removeEntry(quint64 id) override;
    static QString baseKey();

    bool modifyTransportData(const TransportData & data);

    QVector<TransportData> getAllTransport();

    TransportData getTransportById(int id);
    QList<TransportData> getTransportByKey(const QString& key);
    QStringList getManufacturersModels(const QString& name);

    int getInsertTransportId();
    QString getTransportKey(const QString &model, const QString &manufacturer);

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

signals:
    void transportAdded(const TransportData &data);
    void transportModified(const TransportData &data);

private:
    void selectDataFromStorage();
    bool tryToMergeTransport(const TransportData &data);

private:
    DatabaseCommon::LocalDBStorage<TransportData> _storage;
    QSharedPointer<TransportDBProvider> _provider;
    QHash<QString, QSet<QString>> _manufacturersModels;
    QHash<QString, QList<TransportData>> _uniqueTransport;
};

#endif // TRANSPORTDBSERVICE_H
