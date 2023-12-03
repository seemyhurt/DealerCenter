#include "transportdbservice.h"
#include <QDebug>
#include "../Providers/transportdbprovider.h"
#include "../Providers/localbbstorage.h"
#include "../Common/transportdata.h"

TransportDBService::TransportDBService(QObject *parent) :
    ILocalDBServiceBase(parent),
    _provider(QSharedPointer<TransportDBProvider>::create())
{
    if(!_provider)
        qDebug() << "Provider is null";

    connect(_provider.data(), &TransportDBProvider::dbConnectionChanged,
            this, &TransportDBService::handleDbConnectionChange);

    handleDbConnectionChange(_provider->status());
}

quint64 TransportDBService::tableSize() const
{
    return _storage.size();
}

QSqlError TransportDBService::addEntry(QVariantMap &values)
{
    auto data = TransportData::fromDBMap(values);
    auto modelKey = generateTransortKey(data);
    auto knownTransport = _uniqueTransport.contains(modelKey);

    auto id = knownTransport ? _uniqueTransport[modelKey].id
                            : data.id;

    if (_storage.elements().contains(id) || knownTransport)
    {
        _uniqueTransport[modelKey].count += data.count;
        values["id"] = id;
        data.id = id;
        //TODO изменение данных в модели
        return _storage.addEntry(_provider.data(), values, true, data);
    }

    id = _storage.size() + 1;
    values["id"] = id;
    data.id = id;
    _uniqueTransport.insert(modelKey, data);

    auto err = _storage.addEntry(_provider.data(), values, false, data);
    if (err.type() == QSqlError::NoError)
        emit transportAdded(data);
    return err;
}

QString TransportDBService::generateTransortKey(const TransportData &data)
{
    return QStringLiteral("%1%2%3%4%5%6").arg(data.brand).arg(data.model).arg(data.year).arg(data.condition).arg(data.type).arg(data.guaranteePeriod);
}

QVariantList TransportDBService::getAllTransport()
{
    QVariantList result;
    for (const auto & element : qAsConst(_storage.elements()))
        result << element.toWidgetMap();
    return result;
}

QSqlError TransportDBService::removeEntry(quint64 id)
{
    return _storage.removeEntry(_provider.data(), id);
}

void TransportDBService::handleDbConnectionChange(DatabaseCommon::LocalDBStatus status)
{
    _storage.clear();

    if (status != DatabaseCommon::LocalDBStatus::Connected)
        return;

    if (!_provider)
        return;

    _storage.constructElements(_provider->getCars());
    selectDataFromStorage();
}

void TransportDBService::selectDataFromStorage()
{
    for (const auto &element : qAsConst(_storage.elements()))
        _uniqueTransport.insert(generateTransortKey(element), element);
}

QString TransportDBService::baseKey()
{
    return "TransportDBService";
}

