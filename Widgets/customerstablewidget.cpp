#include "customerstablewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

static const QStringList CustomersInfo = {"ID", "Phone number", "Firstname", "Lastname", "Surname", "Age", "Type", "Password"};

CustomersTableWidget::CustomersTableWidget(QWidget *parent)
    : QWidget(parent),
    _userService(ServiceLocator::service<UserDBService>()),
    _customerModel(QSharedPointer<QStandardItemModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(this);

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
    setLayout(layout);

    connect(_userService.data(), &UserDBService::userAdded, this, &CustomersTableWidget::handleNeedUpdateCustomers);
}

void CustomersTableWidget::handleNeedUpdateCustomers(const UserData& data)
{
    if (data.type != QLatin1String("Customer"))
        return;

    auto userMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(CustomersInfo))
        rowItems << new QStandardItem(userMap[key].toString());;
    _customerModel->appendRow(rowItems);
}
