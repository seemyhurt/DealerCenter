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
    return {};
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
}

QString PurchasesDBService::baseKey()
{
    return "PurchasesDBService";
}
