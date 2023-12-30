#include "mainwidget.h"
#include "administratorwidget.h"
#include "customerwidget.h"
#include "appmenu.h"
#include "managerswidget.h"

#include "../Models/manufacturersmodel.h"
#include "../Models/purchasesmodel.h"
#include "../Models/transportsmodel.h"

#include <QLayout>
#include <QLabel>
#include <QFile>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(1600, 700);
    auto layout = new QVBoxLayout(this);

    _menu = new AppMenu(this);
    layout->setMenuBar(_menu);

    auto purchasesModel = QSharedPointer<PurchasesModel>::create();
    auto transportsModel = QSharedPointer<TransportsModel>::create();
    auto manufacturersModel = QSharedPointer<ManufacturersModel>::create();

    _help = new QLabel(this);
    QFile file(":/Other/help.html");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto htmlText = file.readAll();
        file.close();
        _help->setText(htmlText);
    }
    QFont f("Arial", 10, QFont::Medium);
    _help->setFont(f);

    _customerWidget = new CustomerWidget(transportsModel, purchasesModel, this);
    _administratorWidget = new AdministratorWidget(transportsModel, manufacturersModel, this);
    _managerWidget = new ManagersWidget(purchasesModel, transportsModel, manufacturersModel, this);

    _administratorWidget->hide();
    _managerWidget->hide();
    _customerWidget->hide();
    _help->hide();

    layout->addWidget(_customerWidget);
    layout->addWidget(_administratorWidget);
    layout->addWidget(_managerWidget);
    layout->addWidget(_help);

    connect(_menu, &AppMenu::menuInterfaceChanged, this, &MainWidget::handleNeedChangeInterface);
    connect(_menu, &AppMenu::needShowHelp, this, &MainWidget::handleNeedShowHelp);
    connect(_customerWidget, &CustomerWidget::newUserRegistred, this, &MainWidget::handleSetUserInterface);

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
        _lastAddedWidet = _managerWidget;
        _managerWidget->show();
        break;
    case Interface::Administrator:
        if (!_administratorWidget->loginAdministrator())
            break;

        if(_lastAddedWidet)
            _lastAddedWidet->hide();

        _menu->setState(Interface::Administrator);
        _lastAddedWidet = _administratorWidget;
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
    _lastAddedWidet = _customerWidget;
}

void MainWidget::handleNeedShowHelp()
{
    if(_lastAddedWidet)
        _lastAddedWidet->hide();

    _menu->setState(Interface::Unknown);
    _help->show();
    _lastAddedWidet = _help;
}
