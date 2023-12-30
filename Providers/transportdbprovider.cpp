#include "transportdbprovider.h"
#include "../Common/transportdata.h"
#include "../Services/servicelocator.h"
#include "../Services/coreservice.h"

TransportDBProvider::TransportDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    setContext("transport_data",
               TransportData::DBKeys(),
               "transport.db3",
               ServiceLocator::service<CoreService>()->appDataPath(),
               "TransportDBProvider");
}

QVector<TransportData> TransportDBProvider::getCars()
{
    using CD = TransportData;
    using std::make_pair;

    return getAllElements(make_pair("id", &CD::id),
                          make_pair("model", &CD::model),
                          make_pair("year", &CD::year),
                          make_pair("count", &CD::count),
                          make_pair("condition", &CD::condition),
                          make_pair("receiptDate", &CD::receiptDate),
                          make_pair("manufacturer", &CD::manufacturer));
}

QString TransportDBProvider::baseKey()
{
    return "TransportDBProvider";
}
