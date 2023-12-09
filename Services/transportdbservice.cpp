#include "transportdbservice.h"
#include <QDebug>
#include "../Providers/transportdbprovider.h"
#include "../Providers/localbbstorage.h"
#include "../Common/transportdata.h"
#include "purchasesdbservice.h"
#include "servicelocator.h"
#include "../Common/purchasedata.h"

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

    auto id = _storage.maxId() + 1;
    values["id"] = id;
    data.id = id;

    if (tryToMergeTransport(data))
        return {{}, {}, QSqlError::NoError};

    auto err = _storage.addEntry(_provider.data(), values, data);
    if (err.type() == QSqlError::NoError)
        emit transportAdded(data);
    return err;
}

QVector<TransportData> TransportDBService::getAllTransport()
{
    QVector<TransportData> result;
    result.reserve(_storage.size());
    for (const auto & element : qAsConst(_storage.elements()))
        result << element;
    return result;
}

TransportData TransportDBService::getTransportById(int id)
{
    return _storage.elements().value(id);
}

int TransportDBService::getInsertTransportId()
{
    return _storage.lastInsertId();
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
    auto it = _storage.elements().begin();
    while (it != _storage.elements().end())
    {
        auto copy = it.value();
        if (QDateTime::fromMSecsSinceEpoch(it->receiptDate).date() <= QDate::currentDate())
        {
            copy.inStock = true;
            auto map = copy.toDBMap();
            _storage.addEntry(_provider.data(), map, copy);
        }

        auto nextIt = std::next(it);
        tryToMergeTransport(copy);

        it = nextIt;
    }
}

QString TransportDBService::getTransportKey(const TransportData &data)
{
    return QStringLiteral("%1%2").arg(data.model, data.manufacturer);
}

bool TransportDBService::tryToMergeTransport(const TransportData &data)
{
    auto purchasesService = ServiceLocator::service<PurchasesDBService>();

    auto key = getTransportKey(data);

     if (!_uniqueTransport.contains(key))
    {
        _uniqueTransport[key].push_back(data);
        return false;
    }

    auto & range = _uniqueTransport[key];
    std::pair<int, int> removed = std::make_pair(0, 0);
    for (int i = 0; i < range.size(); i++)
    {
        if (range[i] != data)
            continue;

        range[i].count += data.count;
        auto map = range[i].toDBMap();
        if (_storage.addEntry(_provider.data(), map, range[i]).type() != QSqlError::NoError)
            return false;
        if (_storage.removeEntry(_provider.data(), data.id).type() != QSqlError::NoError)
            return false;
        removed = std::make_pair(data.id, range[i].id);
        emit transportModified(range[i]);
    }

    if(removed == std::make_pair(0, 0))
    {
        _uniqueTransport[key].push_back(data);
        return false;
    }

    auto purchases = purchasesService->getPurchasesByTransport(removed.first);

    for (auto &purchase : purchases)
    {
        purchase.transportId = removed.second;
        auto map = purchase.toDBMap();
        if (purchasesService->addEntry(map).type() != QSqlError::NoError)
            return false;
    }
    return true;
}

QString TransportDBService::baseKey()
{
    return "TransportDBService";
}

