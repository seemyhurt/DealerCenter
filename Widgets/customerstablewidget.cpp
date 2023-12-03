#include "customerstablewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

CustomersTableWidget::CustomersTableWidget(QWidget *parent)
    : QWidget(parent),
    _userService(ServiceLocator::service<UserDBService>()),
    _customerModel(QSharedPointer<QStandardItemModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto layout = new QVBoxLayout(this);

    auto keys = UserData::wigdetKeys();
    _customerModel->setHorizontalHeaderLabels(keys);

    auto users = _userService->getAllUsers();
    for (const auto &user : qAsConst(users))
    {
        auto userMap = user.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(keys))
        {
            auto item =  new QStandardItem(userMap.value(key).toString());
            item->setTextAlignment(Qt::AlignCenter);
            rowItems << item;
        }
        _customerModel->appendRow(rowItems);
    }

    tableView->setModel(_customerModel.data());

    tableView->setSortingEnabled(true);
    int idColumnIndex = keys.indexOf("ID");
    tableView->sortByColumn(idColumnIndex, Qt::AscendingOrder);


    layout->addWidget(tableView);
    setLayout(layout);

    connect(_userService.data(), &UserDBService::userAdded, this, &CustomersTableWidget::handleNeedUpdateCustomers);
}

void CustomersTableWidget::handleNeedUpdateCustomers(const UserData& data)
{
    if (data.type != QLatin1String("Customer"))
        return;

    auto keys = UserData::wigdetKeys();
    auto userMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(keys))
    {
        auto item =  new QStandardItem(userMap.value(key).toString());
        item->setTextAlignment(Qt::AlignCenter);
        rowItems << item;
    }
    _customerModel->appendRow(rowItems);
}
