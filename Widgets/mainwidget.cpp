#include "mainwidget.h"
#include "administratorwidget.h"
#include "customerwidget.h"
#include "appmenu.h"
#include "managerswidget.h"

#include "../Models/manufacturersmodel.h"
#include "../Models/purchasesmodel.h"
#include "../Models/transportsmodel.h"

#include <QLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(1600, 700);
    auto layout = new QVBoxLayout(this);

    _menu = QSharedPointer<AppMenu>::create();
    layout->setMenuBar(_menu.data());

    auto purchasesModel = QSharedPointer<PurchasesModel>::create();
    auto transportsModel = QSharedPointer<TransportsModel>::create();
    auto manufacturersModel = QSharedPointer<ManufacturersModel>::create();

    _customerWidget = QSharedPointer<CustomerWidget>::create(transportsModel, purchasesModel);
    _administratorWidget = QSharedPointer<AdministratorWidget>::create(transportsModel, manufacturersModel);
    _managerWidget = QSharedPointer<ManagersWidget>::create(purchasesModel, transportsModel, manufacturersModel);

    _administratorWidget->hide();
    _managerWidget->hide();
    _customerWidget->hide();

    layout->addWidget(_customerWidget.data());
    layout->addWidget(_administratorWidget.data());
    layout->addWidget(_managerWidget.data());

    connect(_menu.data(), &AppMenu::menuInterfaceChanged, this, &MainWidget::handleNeedChangeInterface);
    connect(_customerWidget.data(), &CustomerWidget::newUserRegistred, this, &MainWidget::handleSetUserInterface);

    setLayout(layout);
}

void MainWidget::handleNeedChangeInterface(const QString & type)
{
    auto state = AppInterface::fromString(type);
    switch (state.state) {
    case Interface::Customer:
        if (!_customerWidget->loginCutomer())
            break;
        handleSetUserInterface();
        break;
    case Interface::Manager:
        if (!_managerWidget->loginManager())
            break;

        if(_lastAddedWidet)
            _lastAddedWidet->hide();

        _menu->setState(Interface::Manager);
        _lastAddedWidet = _managerWidget.data();
        _managerWidget->show();
        break;
    case Interface::Administrator:
        if(_lastAddedWidet)
            _lastAddedWidet->hide();

        _menu->setState(Interface::Administrator);
        _lastAddedWidet = _administratorWidget.data();
        _administratorWidget->show();
        return;
    default:
        return;
    }
}

void MainWidget::handleSetUserInterface()
{
    if(_lastAddedWidet)
        _lastAddedWidet->hide();

    _menu->setState(Interface::Customer);
    _customerWidget->show();
    _lastAddedWidet = _customerWidget.data();
}
