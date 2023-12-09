#include "purchasesdbservice.h"
#include "../Providers/purchasedbprovider.h"
#include "../Providers/localbbstorage.h"
#include "../Common/purchasedata.h"

#include "userdbservice.h"
#include "servicelocator.h"
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

    if (_storage.elements().contains(data.id))
    {
        updatePurchases(data);
        auto err = _storage.addEntry(_provider.data(), values, data);
        if (err.type() == QSqlError::NoError)
            emit purchaseModified(data);
        return err;
    }

    auto id = _storage.maxId() + 1;
    values["id"] = id;
    data.id = id;

    _purchasesByUser[data.userId].push_back(data);
    _purchasesByTransport[data.transportId].push_back(data);

    auto err = _storage.addEntry(_provider.data(), values, data);
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
    auto userService = ServiceLocator::service<UserDBService>();
    for (const auto &element : qAsConst(_storage.elements()))
    {
        _purchasesByUser[element.userId].push_back(element);
        _purchasesByTransport[element.transportId].push_back(element);
    }
}

void PurchasesDBService::updatePurchases(const PurchaseData &data)
{
    for (auto &purchase : _purchasesByUser[data.userId])
    {
        if (purchase.id == data.id)
            purchase = data;
    }

    for (auto &purchase : _purchasesByTransport[data.transportId])
    {
        if (purchase.id == data.id)
            purchase = data;
    }
}

QString PurchasesDBService::baseKey()
{
    return "PurchasesDBService";
}

QVector<PurchaseData> PurchasesDBService::getPurchasesByUser(int userId)
{
    return _purchasesByUser.value(userId);
}

QVector<PurchaseData> PurchasesDBService::getPurchasesByTransport(int transportId)
{
    return _purchasesByTransport.value(transportId);
}
