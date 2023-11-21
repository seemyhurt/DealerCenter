#include "administratorwidget.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

#include <QTabWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

static const QStringList CustomersInfo = {"ID", "Phone number", "Firstname", "Lastname", "Surname", "Age", "Type", "Password"};

AdministratorWidget::AdministratorWidget(QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>()),
    _tabs(QSharedPointer<QTabWidget>::create(this)),
    _customersWidget(QSharedPointer<QWidget>::create(this)),
    _customerModel(QSharedPointer<QStandardItemModel>::create())
{
    QStringList lst;
    lst << "Transport" << "Manufacturers" << "Managers";
    for (const auto &str : qAsConst(lst))
        _tabs->addTab(new QLabel(str, _tabs.data()), str);

    initCustomersWidget();
    _tabs->addTab(_customersWidget.data(), "Customers");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs.data());
    setLayout(_tabs->layout());

    connect(_service.data(), &UserDBService::userAdded, this, &AdministratorWidget::handleNeedUpdateCustomers);
}

void AdministratorWidget::initCustomersWidget()
{
    auto tableView = new QTableView(_customersWidget.data());
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(_customersWidget.data());

    _customerModel->setHorizontalHeaderLabels(CustomersInfo);

    auto users = _service->getAllUsers();
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
    tableView->resize(500, 300);

    layout->addWidget(tableView);
    _customersWidget->setLayout(layout);
}

void AdministratorWidget::handleNeedUpdateCustomers(const UserData& data)
{
    auto userMap = data.toWigdetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(CustomersInfo))
        rowItems << new QStandardItem(userMap[key].toString());;
    _customerModel->appendRow(rowItems);
}
