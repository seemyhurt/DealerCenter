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

    setSortRole(Qt::UserRole);
    sort(0, Qt::DescendingOrder);

    connect(_purchaseService.data(), &PurchasesDBService::purchaseAdded, this, &PurchasesModel::handleNeedUpdatePurchase);
    connect(_transportService.data(), &TransportDBService::transportModified, this, &PurchasesModel::handleNeedModifyPurchase);
}

void PurchasesModel::setCurrentUser(quint64 number)
{
    if (_currentUserNumber == number)
        return;

    _currentUserNumber = number;
    auto purchases = _purchaseService->getPurchasesByUser(number);

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
    auto purchaseItem = new QStandardItem(QString("Покупка от ") + dataDate);

    purchaseItem->setEditable(false);

    auto manufacturerItem = new QStandardItem("Производитель");
    auto userDataItem = new QStandardItem("Данные покупателя");
    auto vehicleDataItem = new QStandardItem("Данные о транспортном средстве");

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
    for (int i = 0; i < rowCount(); ++i)
    {
        auto purchaseItem = item(i);
        for (int j = 0; j < purchaseItem->rowCount(); ++j)
        {
            auto child = purchaseItem->child(j);
            if (child->text() != "Данные о транспортном средстве")
                continue;

            auto count = child->rowCount();
            for (int k = 0; k < count; ++k)
            {
                auto values = child->child(k);
                auto value = values->text();
                auto list = value.split(":", QString::SkipEmptyParts);
                if (list[0] != "ID")
                    continue;

                if (list[1].toInt() != data.id)
                    break;

                child->removeRows(k, count);
                auto transportMap = data.toWidgetMap();
                auto transportKey = TransportData::wigdetKeys();
                for (const auto &key : qAsConst(transportKey))
                    child->appendRow(new QStandardItem(QString("%1: %2").arg(key, transportMap.value(key).toString())));
            }
        }
    }
}

QVariant PurchasesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = itemFromIndex(index);

    if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole)
        return item->text();

    return QVariant();
}
