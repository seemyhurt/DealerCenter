#include "transportsmodel.h"
#include "../Common/transportdata.h"
#include "../Common/manufacturerdata.h"
#include "../Services/servicelocator.h"
#include "../Services/transportdbservice.h"
#include "../Services/manufacturerdbservice.h"

TransportsModel::TransportsModel(QObject * parent) :
    QStandardItemModel(parent),
    _transportService(ServiceLocator::service<TransportDBService>()),
    _manufacturerService(ServiceLocator::service<ManufacturerDBService>())
{
    auto keys = TransportData::wigdetKeys();
    auto manufacturerKeys = ManufacturerData::CustomerKeys();
    setHorizontalHeaderLabels(manufacturerKeys + keys);

    auto transports = _transportService->getAllTransport();

    for (const auto &transport : qAsConst(transports))        
        addTransportToModel(transport);

    connect(_transportService.data(), &TransportDBService::transportAdded, this, &TransportsModel::handleNeedUpdateTransports);
    connect(_transportService.data(), &TransportDBService::transportModified, this, &TransportsModel::handleNeedModifyTransports);
}

void TransportsModel::addTransportToModel(const TransportData &data)
{
    auto keys = TransportData::wigdetKeys();
    auto manufacturerKeys = ManufacturerData::CustomerKeys();

    auto manufacturer = _manufacturerService->getManufacturerByName(data.manufacturer).toTransportInfoMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(manufacturerKeys))
    {
        auto item =  new QStandardItem(manufacturer.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }

    auto transportMap = data.toWidgetMap();
    for (const auto &key : qAsConst(keys))
    {
        auto item =  new QStandardItem(transportMap.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }
    appendRow(rowItems);
}

void TransportsModel::handleNeedUpdateTransports(const TransportData& data)
{
    addTransportToModel(data);
}

void TransportsModel::handleNeedModifyTransports(const TransportData &data)
{
    auto keys = TransportData::wigdetKeys();
    auto manufacturerKeys = ManufacturerData::CustomerKeys();

    auto manufacturer = _manufacturerService->getManufacturerByName(data.manufacturer).toTransportInfoMap();
    auto transportMap = data.toWidgetMap();

    auto rows = rowCount();
    auto columns = columnCount();

    for (int i = 0; i < rows; ++i)
    {
        bool isFind = true;
        int countField = 0, dateField = 0;

        for (int j = 0; j < columns; ++j)
        {
            auto headerItem = horizontalHeaderItem(j);
            if (!headerItem) continue;

            auto key = headerItem->text();
            if (key == "Count")
            {
                countField = j;
                continue;
            }

            if (key == "Receipt date")
            {
                dateField = j;
                continue;
            }

            auto transportItem = item(i, j);
            if (!transportItem) continue;

            QString newValue;

            if (manufacturer.contains(key))
                newValue = manufacturer.value(key).toString();
            else if (transportMap.contains(key))
                newValue = transportMap.value(key).toString();

            if (transportItem->text() != newValue)
            {
                isFind = false;
                break;
            }
        }

        if (!isFind) continue;

        auto countItem = item(i, countField);
        if (countItem)
            countItem->setData(data.count, Qt::DisplayRole);

        auto dateItem = item(i, dateField);
        if (dateItem)
            dateItem->setData(data.receiptDate == 0 ? "Unavailable"
                                                    : QDateTime::fromMSecsSinceEpoch(data.receiptDate).toString("dd.MM.yyyy"),
                              Qt::DisplayRole);
        return;
    }
}

