#include "transportdbprovider.h"
#include "../Common/transportdata.h"
#include "../Services/servicelocator.h"
#include "../Services/coreservice.h"

TransportDBProvider::TransportDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    QVector<DatabaseCommon::LocalDBColumn> columns{
                                                   {"id"},
                                                   {"brand"},
                                                   {"model"},
                                                   {"price"},
                                                   {"year"},
                                                   {"count"},
                                                   {"condition"},
                                                   {"type"},
                                                   {"inStock"},
                                                   {"receiptDate"},
                                                   {"guaranteePeriod"}
    };

    setContext("car_data",
               columns,
               "cars.db3",
               ServiceLocator::service<CoreService>()->appDataPath(),
               "TransportDBProvider");
}

QVector<TransportData> TransportDBProvider::getCars()
{
    using CD = TransportData;
    using std::make_pair;

    return getAllElements(make_pair("id", &CD::id),
                          make_pair("brand", &CD::brand),
                          make_pair("model", &CD::model),
                          make_pair("price", &CD::price),
                          make_pair("year", &CD::year),
                          make_pair("count", &CD::count),
                          make_pair("condition", &CD::condition),
                          make_pair("type", &CD::type),
                          make_pair("inStock", &CD::inStock),
                          make_pair("receiptDate", &CD::receiptDate),
                          make_pair("guaranteePeriod", &CD::guaranteePeriod));
}

QString TransportDBProvider::baseKey()
{
    return "TransportDBProvider";
}
