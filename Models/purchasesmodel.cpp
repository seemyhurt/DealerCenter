#include "purchasesmodel.h"

#include "../Common/purchasedata.h"
#include "../Common/manufacturerdata.h"
#include "../Common/userdata.h"
#include "../Common/transportdata.h"

#include "../Services/servicelocator.h"
#include "../Services/purchasesdbservice.h"
#include "../Services/manufacturerdbservice.h"
#include "../Services/transportdbservice.h"
#include "../Services/userdbservice.h"

PurchasesModel::PurchasesModel(QObject * parent) :
    QStandardItemModel(parent),
    _purchaseService(ServiceLocator::service<PurchasesDBService>()),
    _transportService(ServiceLocator::service<TransportDBService>()),
    _userService(ServiceLocator::service<UserDBService>()),
    _manufacturerService(ServiceLocator::service<ManufacturerDBService>())
{
    auto purchases = _purchaseService->getPurchasesByUser(9);

    for (const auto &purchaseData : qAsConst(purchases))
    {
        QStandardItem *purchaseItem = new QStandardItem(QString("Покупка %1").arg(purchaseData.id));
        purchaseItem->setEditable(false);

        QStandardItem *manufacturerItem = new QStandardItem("Производитель");
        QStandardItem *userDataItem = new QStandardItem("Данные пользователя");
        QStandardItem *vehicleDataItem = new QStandardItem("Данные о транспортном средстве");

        purchaseItem->appendRow(manufacturerItem);
        purchaseItem->appendRow(userDataItem);
        purchaseItem->appendRow(vehicleDataItem);

        appendRow(purchaseItem);

        // Дополнительные данные о производителе
        auto manufacturerMap = _manufacturerService->getManufacturerById(purchaseData.manufacturerId).toWidgetMap();
        for (const auto &key : manufacturerMap.keys())
        {
            auto item = new QStandardItem(QString("%1: %2").arg(key, manufacturerMap.value(key).toString()));
            manufacturerItem->appendRow(item);
        }


        auto userMap = _userService->getUserById(purchaseData.userId).toWidgetMap();

        for (const auto &key : userMap.keys())
        {
            auto item = new QStandardItem(QString("%1: %2").arg(key, userMap.value(key).toString()));
            userDataItem->appendRow(item);
        }

        auto transportMap = _transportService->getTransportById(purchaseData.transportId).toWidgetMap();

        QList<QStandardItem*> transportItems;
        for (const auto &key : qAsConst(transportMap))
        {
            auto item =  new QStandardItem(key.toString());
            item->setTextAlignment(Qt::AlignCenter);
            transportItems << item;
        }
        vehicleDataItem->appendRow(transportItems);
    }

    connect(_purchaseService.data(), &PurchasesDBService::purchaseAdded, this, &PurchasesModel::handleNeedUpdatePurchase);
}

void PurchasesModel::handleNeedUpdatePurchase(const PurchaseData& data)
{
    auto keys = PurchaseData::wigdetKeys();
    auto purchaseMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto & key : qAsConst(keys))
    {
        auto item =  new QStandardItem(purchaseMap.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }
    appendRow(rowItems);
}
