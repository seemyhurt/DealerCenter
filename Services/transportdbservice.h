#ifndef TRANSPORTDBSERVICE_H
#define TRANSPORTDBSERVICE_H

#include "ilocaldbservicebase.h"
#include "../Providers/localbbstorage.h"
#include <QSharedPointer>
#include "../Common/transportdata.h"

class TransportDBProvider;

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

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

private:
    void selectDataFromStorage();

private:
    DatabaseCommon::LocalDBStorage<TransportData> _storage;
    QSharedPointer<TransportDBProvider> _provider;

};

#endif // TRANSPORTDBSERVICE_H
