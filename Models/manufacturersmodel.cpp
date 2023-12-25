#include "manufacturersmodel.h"
#include "../Services/manufacturerdbservice.h"
#include "../Services/servicelocator.h"
#include "../Common/manufacturerdata.h"

ManufacturersModel::ManufacturersModel(QObject * parent) :
    QStandardItemModel(parent),
    _manufacturersService(ServiceLocator::service<ManufacturerDBService>())
{
    auto keys = ManufacturerData::wigdetKeys();
    setHorizontalHeaderLabels(keys);

    auto manufacturers = _manufacturersService->getAllManufacturers();

    for (const auto &manufacturer : qAsConst(manufacturers))
    {
        auto manufacturerMap = manufacturer.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(keys))
        {
            auto item =  new QStandardItem(manufacturerMap.value(key).toString());
            item->setTextAlignment(Qt::AlignCenter);
            rowItems << item;
        }
        appendRow(rowItems);
    }

    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &ManufacturersModel::handleNeedUpdateManufacturers);
}

void ManufacturersModel::handleNeedUpdateManufacturers(const ManufacturerData& data)
{
    auto keys = ManufacturerData::wigdetKeys();
    auto manufacturerMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto & key : qAsConst(keys))
    {
        auto item =  new QStandardItem(manufacturerMap.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }
    appendRow(rowItems);
}

bool ManufacturersModel::addNewManufacturer(const ManufacturerData& data)
{
    auto manufacturerDbdata = data.toDBMap();
    if (_manufacturersService->isManufacturerExists(data.name))
        return false;

    if (_manufacturersService->addEntry(manufacturerDbdata).type() == QSqlError::NoError)
        return true;
    else return false;
}

QStringList ManufacturersModel::getAvailableBrands()
{
    return _manufacturersService->getAvailableBrands();
}
