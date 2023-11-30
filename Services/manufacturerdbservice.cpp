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

//    if (_storage.elements().contains(data.id))
//    {
//        for (auto &element : _namesToBrand[data.carBrand])
//        {
//            if (element.id == data.id)
//                element = data;
//        }
//        //TODO изменение данных в модели
//        return _storage.addEntry(_provider.data(), values, true, data);
//    }

    auto id = _storage.size() + 1;
    values["id"] = id;
    data.id = id;
    _namesToBrand[data.carBrand].push_back(data.name);
    _brandsToType[data.type].insert(data.carBrand);
    _manufacturers.insert(data.name, data);

    auto err = _storage.addEntry(_provider.data(), values, false, data);
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
        _namesToBrand[element.carBrand] << element.name;
        _brandsToType[element.type].insert(element.carBrand);
        _manufacturers.insert(element.name, element);
    }
}

QVariantList ManufacturerDBService::getAllManufacturers()
{
    QVariantList result;
    for (const auto & element : qAsConst(_storage.elements()))
        result << element.toWidgetMap();
    return result;
}

QStringList ManufacturerDBService::getManufacturersByBrand(const QString & brand)
{
    return _namesToBrand.value(brand);
}

QStringList ManufacturerDBService::getManufacturersByType(const QString & type)
{
    QStringList result;
    const auto & brands = _brandsToType[type];
    result.reserve(brands.size());
    for (const auto &brand : qAsConst(brands))
        result << brand;
    return result;
}

ManufacturerData ManufacturerDBService::getManufacturerInfo(const QString & name)
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

