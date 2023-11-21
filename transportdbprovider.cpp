#include "transportdbprovider.h"
#include "transportdata.h"
#include "servicelocator.h"
#include "coreservice.h"

TransportDBProvider::TransportDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    QVector<DatabaseCommon::LocalDBColumn> columns{
                               {"id"},
                               {"brand"},
                               {"model"},
                               {"price"},
                               {"state"},
                               {"year"},
                               {"count"},
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
                          make_pair("count", &CD::count));
}

QString TransportDBProvider::baseKey()
{
    return "TransportDBProvider";
}
