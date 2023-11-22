#include "administratorwidget.h"
#include "inputmanufacturerdialog.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"
#include "../Services/manufacturerdbservice.h"
#include "../Common/manufacturerdata.h"

#include <QTabWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

static const QStringList CustomersInfo = {"ID", "Phone number", "Firstname", "Lastname", "Surname", "Age", "Type", "Password"};
static const QStringList ManufacturersInfo = {"ID", "Name", "Delivery time", "Guarantee period", "Car brand"};

AdministratorWidget::AdministratorWidget(QWidget *parent)
    : QWidget(parent),
    _tabs(QSharedPointer<QTabWidget>::create(this)),
    _userService(ServiceLocator::service<UserDBService>()),
    _customersWidget(QSharedPointer<QWidget>::create(this)),
    _customerModel(QSharedPointer<QStandardItemModel>::create()),
    _manufacturersService(ServiceLocator::service<ManufacturerDBService>()),
    _manufacturersWidget(QSharedPointer<QWidget>::create(this)),
    _manufacturersModel(QSharedPointer<QStandardItemModel>::create())
{
    QStringList lst;
    lst << "Transport" << "Managers";
    for (const auto &str : qAsConst(lst))
        _tabs->addTab(new QLabel(str, _tabs.data()), str);

    initCustomersWidget();
    initManufacturersWidget();
    _tabs->addTab(_customersWidget.data(), "Customers");
    _tabs->addTab(_manufacturersWidget.data(), "Manufacturers");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs.data());
    setLayout(_tabs->layout());

    connect(_userService.data(), &UserDBService::userAdded, this, &AdministratorWidget::handleNeedUpdateCustomers);
    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &AdministratorWidget::handleNeedUpdateManufacturers);
}

void AdministratorWidget::initCustomersWidget()
{
    auto tableView = new QTableView(_customersWidget.data());
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(_customersWidget.data());

    _customerModel->setHorizontalHeaderLabels(CustomersInfo);

    auto users = _userService->getAllUsers();
    for (const auto &user : qAsConst(users))
    {
        auto userMap = user.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(CustomersInfo))
            rowItems << new QStandardItem(userMap[key].toString());;
        _customerModel->appendRow(rowItems);
    }

    tableView->setModel(_customerModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(tableView);
    _customersWidget->setLayout(layout);
}

void AdministratorWidget::initManufacturersWidget()
{
    auto tableView = new QTableView(_manufacturersWidget.data());
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(_manufacturersWidget.data());

    _manufacturersModel->setHorizontalHeaderLabels(ManufacturersInfo);

    auto manufacturers = _manufacturersService->getAllManufacturers();
    for (const auto &manufacturer : qAsConst(manufacturers))
    {
        auto manufacturerMap = manufacturer.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(ManufacturersInfo))
            rowItems << new QStandardItem(manufacturerMap[key].toString());;
        _manufacturersModel->appendRow(rowItems);
    }

    tableView->setModel(_manufacturersModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto buttonAdd = new QPushButton("Добавить производителя", _manufacturersWidget.data());
    connect(buttonAdd, &QPushButton::clicked, this, &AdministratorWidget::handleNeedAddManufacturer);

    layout->addWidget(tableView);
    layout->addWidget(buttonAdd);
    _manufacturersWidget->setLayout(layout);
}

void AdministratorWidget::handleNeedUpdateCustomers(const UserData& data)
{
    auto userMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(CustomersInfo))
        rowItems << new QStandardItem(userMap[key].toString());;
    _customerModel->appendRow(rowItems);
}

void AdministratorWidget::handleNeedUpdateManufacturers(const ManufacturerData& data)
{
    auto manufacturerMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(ManufacturersInfo))
        rowItems << new QStandardItem(manufacturerMap[key].toString());;
    _manufacturersModel->appendRow(rowItems);
}

void AdministratorWidget::handleNeedAddManufacturer()
{
    auto dialog = new InputManufacturerDialog();
    if (dialog->exec() != QDialog::Accepted)
        return;

    auto manufacturer = dialog->getDialogInfo();
    delete dialog;

    auto manufacturerDbdata = manufacturer.toDBMap();
    if (_manufacturersService->addEntry(manufacturerDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "Manufacturer successfully added!");
        return;
    }

    QMessageBox::warning(nullptr, "Error", "Incorrect manufacturer data");
}
