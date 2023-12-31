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

    auto id = _storage.maxId() + 1;
    values["id"] = id;
    data.id = id;

    _namesToBrand[data.transportBrand].push_back(data.name);
    _brandsToType[data.type].insert(data.transportBrand);
    _manufacturers.insert(data.name, data);

    auto err = _storage.addEntry(_provider.data(), values, data);
    if (err.type() == QSqlError::NoError)
        emit manufacturerAdded(data);
    return err;
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
    for (const auto & element : qAsConst(_storage.elements()))
    {
        _namesToBrand[element.transportBrand] << element.name;
        _brandsToType[element.type].insert(element.transportBrand);
        _manufacturers.insert(element.name, element);
    }
}

QVector<ManufacturerData> ManufacturerDBService::getAllManufacturers()
{
    QVector<ManufacturerData> result;
    result.reserve(_storage.size());
    for (const auto & element : qAsConst(_storage.elements()))
        result << element;
    return result;
}

QStringList ManufacturerDBService::getManufacturersByBrand(const QString & brand)
{
    return _namesToBrand.value(brand);
}

QStringList ManufacturerDBService::getBrandsByType(const QString & type)
{
    QStringList result;
    const auto & brands = _brandsToType[type];
    result.reserve(brands.size());
    for (const auto &brand : qAsConst(brands))
        result << brand;
    return result;
}

ManufacturerData ManufacturerDBService::getManufacturerById(int id)
{
    return _storage.elements().value(id);
}

bool ManufacturerDBService::isManufacturerExists(const QString &name)
{
    return _manufacturers.contains(name);
}

ManufacturerData ManufacturerDBService::getManufacturerByName(const QString & name)
{
    return _manufacturers.value(name);
}

QStringList ManufacturerDBService::getAvailableTypes()
{
    return _brandsToType.keys();
}

QStringList ManufacturerDBService::getAvailableBrands()
{
    return _namesToBrand.keys();
}

QString ManufacturerDBService::baseKey()
{
    return "ManufacturerDBService";
}

