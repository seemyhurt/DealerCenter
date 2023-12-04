#ifndef PURCHASESDBSERVICE_H
#define PURCHASESDBSERVICE_H

#include <QSharedPointer>
#include "ilocaldbservicebase.h"
#include "../Providers/localbbstorage.h"

class PurchaseDBProvider;
struct PurchaseData;

class PurchasesDBService : public DatabaseCommon::ILocalDBServiceBase
{
    Q_OBJECT
public:
    explicit PurchasesDBService(QObject *parent = nullptr);

    // ILocalDBServiceBase interface
    quint64 tableSize() const override;
    QSqlError addEntry(QVariantMap &values) override;
    QSqlError removeEntry(quint64 id) override;

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();

    QVector<PurchaseData> getPurchasesByUser(int userId);

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

signals:
    void purchaseAdded(const PurchaseData &data);

private:
    void selectDataFromStorage();

private:
    DatabaseCommon::LocalDBStorage<PurchaseData> _storage;
    QSharedPointer<PurchaseDBProvider> _provider;

    QHash<int, QVector<PurchaseData>> _purchasesbyUser;

};

#endif // PURCHASESDBSERVICE_H
