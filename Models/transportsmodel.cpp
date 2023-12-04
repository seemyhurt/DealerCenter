#include "transportsmodel.h"
#include "../Common/transportdata.h"
#include "../Services/servicelocator.h"
#include "../Services/transportdbservice.h"

TransportsModel::TransportsModel(QObject * parent) :
    QStandardItemModel(parent),
    _transportService(ServiceLocator::service<TransportDBService>())
{
    auto keys = TransportData::wigdetKeys();
    setHorizontalHeaderLabels(keys);

    auto transports = _transportService->getAllTransport();

    for (const auto &transport : qAsConst(transports))
    {
        auto transportMap = transport.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(keys))
        {
            auto item =  new QStandardItem(transportMap.value(key).toString());
            item->setTextAlignment(Qt::AlignCenter);
            rowItems << item;
        }
        appendRow(rowItems);
    }

    connect(_transportService.data(), &TransportDBService::transportAdded, this, &TransportsModel::handleNeedUpdateTransports);
}

void TransportsModel::handleNeedUpdateTransports(const TransportData& data)
{
    auto keys = TransportData::wigdetKeys();
    auto transportMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto & key : qAsConst(keys))
    {
        auto item =  new QStandardItem(transportMap.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }
    appendRow(rowItems);
}

