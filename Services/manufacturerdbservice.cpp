#include "manufacturerdbservice.h"
#include "../Providers/manufacturerdbprovider.h"
#include "../Common/manufacturerdata.h"

#include <QDebug>

ManufacturerDBService::ManufacturerDBService(QObject *parent) :
    ILocalDBServiceBase(parent),
    _provider(QSharedPointer<ManufacturerDBProvider>::create())
{
    if(!_provider)
        qDebug() << "Provider is null";

    connect(_provider.data(), &ManufacturerDBProvider::dbConnectionChanged,
            this, &ManufacturerDBService::handleDbConnectionChange);

    handleDbConnectionChange(_provider->status());
}

quint64 ManufacturerDBService::tableSize() const
{
    return _storage.size();
}

QSqlError ManufacturerDBService::addEntry(QVariantMap &values)
{

    auto data = ManufacturerData::fromDBMap(values);

    auto id = _storage.size() + 1;
    values["id"] = id;
    data.id = id;

    return _storage.addEntry(_provider.data(), values, false, data);
}

QSqlError ManufacturerDBService::removeEntry(quint64 id)
{
    return _storage.removeEntry(_provider.data(), id);
}

void ManufacturerDBService::handleDbConnectionChange(DatabaseCommon::LocalDBStatus status)
{
    _storage.clear();

    if (status != DatabaseCommon::LocalDBStatus::Connected)
        return;

    if (!_provider)
        return;

    _storage.constructElements(_provider->getManufacturers());
    selectDataFromStorage();
}

void ManufacturerDBService::selectDataFromStorage()
{

}

QString ManufacturerDBService::baseKey()
{
    return "ManufacturerDBService";
}

