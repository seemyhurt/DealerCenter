#include "mainwidget.h"
#include "administratorwidget.h"
#include "customerwidget.h"
#include "appmenu.h"
#include "managerswidget.h"
#include <QLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(800, 600);
    _currentLayout = QSharedPointer<QVBoxLayout>::create(this);

    _menu = QSharedPointer<AppMenu>::create();
    _currentLayout->setMenuBar(_menu.data());

    _customerWidget = QSharedPointer<CustomerWidget>::create();
    _administratorWidget = QSharedPointer<AdministratorWidget>::create();
    _managerWidget = QSharedPointer<ManagersWidget>::create();

    _administratorWidget->hide();
    _managerWidget->hide();
    _customerWidget->hide();

    _currentLayout->addWidget(_customerWidget.data());
    _currentLayout->addWidget(_administratorWidget.data());
    _currentLayout->addWidget(_managerWidget.data());

    connect(_menu.data(), &AppMenu::menuInterfaceChanged, this, &MainWidget::handleNeedChangeInterface);
    connect(_customerWidget.data(), &CustomerWidget::newUserRegistred, this, &MainWidget::handleSetUserInterface);

    setLayout(_currentLayout.data());
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
