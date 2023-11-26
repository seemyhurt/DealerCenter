#include "manufacturersmodel.h"
#include "../Services/manufacturerdbservice.h"
#include "../Services/servicelocator.h"
#include "../Common/manufacturerdata.h"

static const QStringList ManufacturersInfo = {"ID", "Name", "Delivery time, days", "Guarantee period, years", "Car brand"};

ManufacturersModel::ManufacturersModel(QObject * parent) :
    QStandardItemModel(parent),
    _manufacturersService(ServiceLocator::service<ManufacturerDBService>())
{
    setHorizontalHeaderLabels(ManufacturersInfo);

    auto manufacturers = _manufacturersService->getAllManufacturers();
    for (const auto &manufacturer : qAsConst(manufacturers))
    {
        auto manufacturerMap = manufacturer.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(ManufacturersInfo))
            rowItems << new QStandardItem(manufacturerMap[key].toString());;
        appendRow(rowItems);
    }

    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &ManufacturersModel::handleNeedUpdateManufacturers);
}

void ManufacturersModel::handleNeedUpdateManufacturers(const ManufacturerData& data)
{
    auto manufacturerMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(ManufacturersInfo))
        rowItems << new QStandardItem(manufacturerMap[key].toString());;
    appendRow(rowItems);
}

bool ManufacturersModel::addNewManufacturer(const ManufacturerData& data)
{
    auto manufacturerDbdata = data.toDBMap();
    if (_manufacturersService->addEntry(manufacturerDbdata).type() == QSqlError::NoError)
        return true;
    else return false;
}

QStringList ManufacturersModel::getAvailableBrands()
{
    return _manufacturersService->getAvailableBrands();
}
