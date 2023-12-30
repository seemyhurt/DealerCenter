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
    auto purchases = _purchaseService->getPurchasesByUser(_currentUserNumber);

    for (const auto &purchaseData : qAsConst(purchases))
        generatePurchaseItem(purchaseData);

    connect(_purchaseService.data(), &PurchasesDBService::purchaseAdded, this, &PurchasesModel::handleNeedUpdatePurchase);
    connect(_transportService.data(), &TransportDBService::transportModified, this, &PurchasesModel::handleNeedModifyPurchase);
}

void PurchasesModel::setCurrentUser(quint64 number)
{
    if (_currentUserNumber == number)
        return;

    clear();
    _currentUserNumber = number;
    auto user = _userService->getUserByNumber(_currentUserNumber);
    auto purchases = _purchaseService->getPurchasesByUser(user.id);

    for (const auto &purchaseData : qAsConst(purchases))
        generatePurchaseItem(purchaseData);
}

void PurchasesModel::handleNeedUpdatePurchase(const PurchaseData& data)
{
    generatePurchaseItem(data);
}

void PurchasesModel::generatePurchaseItem(const PurchaseData &data)
{
    auto dataDate = QDateTime::fromMSecsSinceEpoch(data.date).toString("dd.MM.yyyy HH:mm");
    auto countStr = QStringLiteral(" of %1 units").arg(data.count);
    auto priceStr = QStringLiteral(" worth %1").arg(data.price);
    auto purchaseItem = new QStandardItem(QStringLiteral("Purchase on  ") + dataDate + countStr + priceStr);

    purchaseItem->setEditable(false);

    auto manufacturerItem = new QStandardItem("Manufacturer");
    auto userDataItem = new QStandardItem("Buyer");
    auto vehicleDataItem = new QStandardItem("Vehicle data");

    purchaseItem->appendRow(manufacturerItem);
    purchaseItem->appendRow(userDataItem);
    purchaseItem->appendRow(vehicleDataItem);

    appendRow(purchaseItem);

    auto manufacturerMap = _manufacturerService->getManufacturerById(data.manufacturerId).toWidgetMap();
    auto manufacturerKey = ManufacturerData::wigdetKeys();
    for (const auto &key : qAsConst(manufacturerKey))
    {
        auto item = new QStandardItem(QString("%1: %2").arg(key, manufacturerMap.value(key).toString()));
        manufacturerItem->appendRow(item);
    }

    auto userMap = _userService->getUserById(data.userId).toWidgetMap();
    auto userKey = UserData::wigdetKeys();
    for (const auto &key : qAsConst(userKey))
    {
        auto item = new QStandardItem(QString("%1: %2").arg(key, userMap.value(key).toString()));
        userDataItem->appendRow(item);
    }

    auto transportMap = _transportService->getTransportById(data.transportId).toWidgetMap();
    auto transportKey = TransportData::wigdetKeys();
    for (const auto &key : qAsConst(transportKey))
    {
        auto item = new QStandardItem(QString("%1: %2").arg(key, transportMap.value(key).toString()));
        vehicleDataItem->appendRow(item);
    }
}

void PurchasesModel::handleNeedModifyPurchase(const TransportData& data)
{
    auto transportMap = data.toWidgetMap();
    for (int i = 0; i < rowCount(); ++i)
    {
        auto purchaseItem = item(i);
        for (int j = 0; j < purchaseItem->rowCount(); ++j)
        {
            auto child = purchaseItem->child(j);
            if (child->text() != "Vehicle data")
                continue;

            bool isFind = true;
            auto count = child->rowCount();
            for (int k = 0; k < count; ++k)
            {
                auto values = child->child(k);
                auto value = values->text();
                auto list = value.split(": ", QString::SkipEmptyParts);

                if (list.size() != 2)
                    continue;

                if (list[0] == "Count")
                    continue;

                if (list[0] == "Receipt date")
                    continue;

                auto val = transportMap.value(list[0]).toString();
                if (list[1] != val)
                {
                    isFind = false;
                    break;
                }
            }
            if (!isFind)
                continue;

            purchaseItem->removeRow(j);

            auto vehicleDataItem = new QStandardItem("Vehicle data");
            purchaseItem->appendRow(vehicleDataItem);
            auto transportKey = TransportData::wigdetKeys();
            for (const auto &key : qAsConst(transportKey))
            {
                auto item = new QStandardItem(QString("%1: %2").arg(key, transportMap.value(key).toString()));
                vehicleDataItem->appendRow(item);
            }
        }
    }
}
