#include "purchasedbprovider.h"

#include "../Common/purchasedata.h"
#include "../Services/servicelocator.h"
#include "../Services/coreservice.h"

PurchaseDBProvider::PurchaseDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    setContext("purchase_data",
               PurchaseData::DBKeys(),
               "purchases.db3",
               ServiceLocator::service<CoreService>()->appDataPath(),
               "PurchaseDBProvider");
}

QVector<PurchaseData> PurchaseDBProvider::getPurchases()
{
    using PD = PurchaseData;
    using std::make_pair;

    return getAllElements(make_pair("id", &PD::id),
                          make_pair("userId", &PD::userId),
                          make_pair("transportId", &PD::transportId),
                          make_pair("manufacturerId", &PD::manufacturerId),
                          make_pair("count", &PD::count),
                          make_pair("date", &PD::date),
                          make_pair("price", &PD::price));
}

QString PurchaseDBProvider::baseKey()
{
    return "PurchaseDBProvider";
}
