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

    if (_storage.elements().contains(data.id))
    {
        for (auto &element : _manufacturersToBrand[data.carBrand])
        {
            if (element.id == data.id)
                element = data;
        }
        //TODO изменение данных в модели
        return _storage.addEntry(_provider.data(), values, true, data);
    }

    auto id = _storage.size() + 1;
    values["id"] = id;
    data.id = id;
    _manufacturersToBrand[data.carBrand].push_back(data);

    emit manufacturerAdded(data);
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
    for (const auto & element : qAsConst(_storage.elements()))
        _manufacturersToBrand[element.carBrand].push_back(element);
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
    QStringList result;
    const auto &manufacturers = _manufacturersToBrand.value(brand);
    for (const auto &manufacturer : qAsConst(manufacturers))
        result << manufacturer.name;
    return result;
}
QStringList ManufacturerDBService::getAvailableBrands()
{
    return _manufacturersToBrand.keys();
}

QString ManufacturerDBService::baseKey()
{
    return "ManufacturerDBService";
}

