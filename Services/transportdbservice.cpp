#include "transportdbservice.h"
#include <QDebug>
#include "../Providers/transportdbprovider.h"
#include "../Providers/localbbstorage.h"

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
    return {};
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
}

QString TransportDBService::baseKey()
{
    return "TransportDBService";
}

