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

static const QStringList ManagersInfo = {"ID", "Phone number", "Firstname", "Lastname", "Surname", "Age", "Type", "Password"};

ManagersTableWidget::ManagersTableWidget(QWidget *parent)
    : QWidget(parent),
    _usersService(ServiceLocator::service<UserDBService>()),
    _managersModel(QSharedPointer<QStandardItemModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto layout = new QVBoxLayout(this);

    _managersModel->setHorizontalHeaderLabels(ManagersInfo);

    auto managers = _usersService->getAllManagers();
    for (const auto &user : qAsConst(managers))
    {
        auto userMap = user.toMap();

        QList<QStandardItem*> rowItems;
        for (const auto &key : qAsConst(ManagersInfo))
            rowItems << new QStandardItem(userMap[key].toString());;
        _managersModel->appendRow(rowItems);
    }

    tableView->setModel(_managersModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

    auto userMap = data.toWidgetMap();

    QList<QStandardItem*> rowItems;
    for (const auto &key : qAsConst(ManagersInfo))
        rowItems << new QStandardItem(userMap[key].toString());;
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
    if (_usersService->addEntry(managerDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "Manager successfully added!");
        return;
    }

    QMessageBox::warning(nullptr, "Error", "Incorrect manager data");
}
