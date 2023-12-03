#include "manufacturerdbprovider.h"
#include "../Services/coreservice.h"
#include "../Services/servicelocator.h"
#include "../Common/manufacturerdata.h"

ManufacturerDBProvider::ManufacturerDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    QVector<DatabaseCommon::LocalDBColumn> columns{
                                                   {"id"},
                                                   {"name"},
                                                   {"deliveryTime"},
                                                   {"guaranteePeriod"},
                                                   {"transportBrand"},
                                                   {"type"}
                                                   };

    setContext("manufacturer_data",
               columns,
               "manufacturer.db3",
               ServiceLocator::service<CoreService>()->appDataPath(),
               "ManufacturerDBProvider");
}

QVector<ManufacturerData> ManufacturerDBProvider::getManufacturers()
{
    using MD = ManufacturerData;
    using std::make_pair;

    return getAllElements(make_pair("id", &MD::id),
                          make_pair("name", &MD::name),
                          make_pair("deliveryTime", &MD::deliveryTime),
                          make_pair("guaranteePeriod", &MD::guaranteePeriod),
                          make_pair("transportBrand", &MD::transportBrand),
                          make_pair("type", &MD::type));
}

QString ManufacturerDBProvider::baseKey()
{
    return "ManufacturerDBProvider";
}
