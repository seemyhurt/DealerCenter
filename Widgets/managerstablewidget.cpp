#include "managerstablewidget.h"
#include "inputuserdialog.h"

#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"
#include "../Common/userdata.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QMessageBox>

ManagersTableWidget::ManagersTableWidget(QWidget *parent)
    : QWidget(parent),
    _usersService(ServiceLocator::service<UserDBService>()),
    _managersModel(QSharedPointer<QStandardItemModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(this);

    auto keys = UserData::wigdetKeys();
    _managersModel->setHorizontalHeaderLabels(keys);

    auto managers = _usersService->getAllManagers();
    for (const auto &user : qAsConst(managers))
    {
        auto userMap = user.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(keys))
        {
            auto item =  new QStandardItem(userMap.value(key).toString());
            item->setTextAlignment(Qt::AlignCenter);
            rowItems << item;
        }
        _managersModel->appendRow(rowItems);
    }

    tableView->setModel(_managersModel.data());

    tableView->setSortingEnabled(true);
    int idColumnIndex = keys.indexOf("ID");
    tableView->sortByColumn(idColumnIndex, Qt::AscendingOrder);

    auto buttonAdd = new QPushButton("Add new manager", this);
    connect(buttonAdd, &QPushButton::clicked, this, &ManagersTableWidget::handleNeedAddManager);

    layout->addWidget(tableView);
    layout->addWidget(buttonAdd);
    setLayout(layout);

    connect(_usersService.data(), &UserDBService::userAdded, this, &ManagersTableWidget::handleNeedUpdateManagers);
}

void ManagersTableWidget::handleNeedUpdateManagers(const UserData& data)
{
    if (data.type != QLatin1String("Manager"))
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
    _managersModel->appendRow(rowItems);
}

void ManagersTableWidget::handleNeedAddManager()
{
    auto dialog = new InputUserDialog();
    if (dialog->exec() != QDialog::Accepted)
        return;

    auto manager = dialog->getDialogInfo();
    delete dialog;

    manager.type = "Manager";
    auto managerDbdata = manager.toDBMap();

    if (_usersService->isUserExist(manager.phoneNumber))
    {
        QMessageBox::warning(nullptr, "Error", "User with that number already exists!");
        return;
    }

    if (_usersService->addEntry(managerDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "Manager successfully added!");
        return;
    }

    QMessageBox::warning(nullptr, "Error", "Incorrect manager data");
}
