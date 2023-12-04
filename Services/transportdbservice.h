#ifndef TRANSPORTDBSERVICE_H
#define TRANSPORTDBSERVICE_H

#include <QSharedPointer>
#include "ilocaldbservicebase.h"
#include "../Providers/localbbstorage.h"

class TransportDBProvider;
struct TransportData;

class TransportDBService : public DatabaseCommon::ILocalDBServiceBase
{
    Q_OBJECT
public:
    explicit TransportDBService(QObject *parent = nullptr);

    // ILocalDBServiceBase interface
    quint64 tableSize() const override;
    QSqlError addEntry(QVariantMap &values) override;
    QSqlError removeEntry(quint64 id) override;

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();

    QVariantList getAllTransport();

    TransportData getTransportById(int id);

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

signals:
    void transportAdded(const TransportData &data);

private:
    void selectDataFromStorage();

    QString generateTransortKey(const TransportData &data);

private:
    DatabaseCommon::LocalDBStorage<TransportData> _storage;
    QSharedPointer<TransportDBProvider> _provider;
    QHash<QString, TransportData> _uniqueTransport;
};

#endif // TRANSPORTDBSERVICE_H
