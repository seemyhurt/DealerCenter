#include "purchasedbprovider.h"

#include "../Common/purchasedata.h"
#include "../Services/servicelocator.h"
#include "../Services/coreservice.h"

PurchaseDBProvider::PurchaseDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    QVector<DatabaseCommon::LocalDBColumn> columns{
                                                    {"id"},
                                                    {"userId"},
                                                    {"transportId"},
                                                    {"count"},
                                                    {"date"}
    };

    setContext("purchase_data",
               columns,
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
                          make_pair("count", &PD::count),
                          make_pair("date", &PD::date));
}

QString PurchaseDBProvider::baseKey()
{
    return "PurchaseDBProvider";
}
