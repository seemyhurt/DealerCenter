#include "mainwidget.h"
#include <QApplication>
#include "coreservice.h"
#include "servicelocator.h"
#include "transportdbservice.h"
#include "userdbservice.h"

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

    auto transportService = QSharedPointer<TransportDBService>::create();
    ServiceLocator::addService(transportService);

    auto userService = QSharedPointer<UserDBService>::create();
    ServiceLocator::addService(userService);
}
