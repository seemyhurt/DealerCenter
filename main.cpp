#include "Widgets/mainwidget.h"
#include <QApplication>
#include "Services/coreservice.h"
#include "Services/servicelocator.h"
#include "Services/transportdbservice.h"
#include "Services/userdbservice.h"
#include "Services/manufacturerdbservice.h"
#include "Services/purchasesdbservice.h"

void initServices();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initServices();

    MainWidget w;
    w.show();
    return a.exec();
}

void initServices()
{
    auto core = QSharedPointer<CoreService>::create("DilerCenter");
    ServiceLocator::addService(core);

    auto userService = QSharedPointer<UserDBService>::create();
    ServiceLocator::addService(userService);

    auto manufacturerService = QSharedPointer<ManufacturerDBService>::create();
    ServiceLocator::addService(manufacturerService);

    auto purchasesService = QSharedPointer<PurchasesDBService>::create();
    ServiceLocator::addService(purchasesService);

    auto transportService = QSharedPointer<TransportDBService>::create();
    ServiceLocator::addService(transportService);
}
