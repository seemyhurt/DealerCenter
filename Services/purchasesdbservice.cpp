#include "purchasesdbservice.h"
#include "../Providers/purchasedbprovider.h"
#include "../Providers/localbbstorage.h"
#include "../Common/purchasedata.h"
#include <QDebug>

PurchasesDBService::PurchasesDBService(QObject *parent) :
    ILocalDBServiceBase(parent),
    _provider(QSharedPointer<PurchaseDBProvider>::create())
{
    if(!_provider)
        qDebug() << "Provider is null";

    connect(_provider.data(), &PurchaseDBProvider::dbConnectionChanged,
            this, &PurchasesDBService::handleDbConnectionChange);

    handleDbConnectionChange(_provider->status());
}

quint64 PurchasesDBService::tableSize() const
{
    return _storage.size();
}

QSqlError PurchasesDBService::addEntry(QVariantMap &values)
{
    auto data = PurchaseData::fromDBMap(values);

    auto id = _storage.size() + 1;
    values["id"] = id;
    data.id = id;

    _purchasesbyUser[data.userId].push_back(data);

    auto err = _storage.addEntry(_provider.data(), values, false, data);
    if (err.type() == QSqlError::NoError)
        emit purchaseAdded(data);
    return err;
}

QSqlError PurchasesDBService::removeEntry(quint64 id)
{
    return _storage.removeEntry(_provider.data(), id);
}

void PurchasesDBService::handleDbConnectionChange(DatabaseCommon::LocalDBStatus status)
{
    _storage.clear();

    if (status != DatabaseCommon::LocalDBStatus::Connected)
        return;

    if (!_provider)
        return;

    _storage.constructElements(_provider->getPurchases());
    selectDataFromStorage();
}

void PurchasesDBService::selectDataFromStorage()
{
    for (const auto &element : qAsConst(_storage.elements()))
    {
        _purchasesbyUser[element.userId].push_back(element);
    }
}

QString PurchasesDBService::baseKey()
{
    return "PurchasesDBService";
}

QVector<PurchaseData> PurchasesDBService::getPurchasesByUser(int userId)
{
    return _purchasesbyUser.value(userId);
}
