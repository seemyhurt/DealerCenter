#include "managerswidget.h"

#include "purchasewidget.h"
#include "logindialog.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"
#include "../Models/manufacturersmodel.h"

#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlError>

ManagersWidget::ManagersWidget(QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>()),
    _manufacturersModel(QSharedPointer<ManufacturersModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);

    auto purchaseWidget = new PurchaseWidget(this);
    auto layout = new QVBoxLayout(this);

    tableView->setModel(_manufacturersModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(tableView);
    layout->addWidget(purchaseWidget);
    setLayout(layout);
}

bool ManagersWidget::loginManager()
{
    auto dialog = new LoginDialog(false, this);
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto loginInfo = dialog->getDialogInfo();

    if (!_service->isUserExist(loginInfo.first))
    {
        QMessageBox::warning(nullptr, "Error", "Manager not exists, contact the administrator!");
        return false;
    }

    if (!_service->isPasswordCorrect(loginInfo.first, loginInfo.second))
    {
        QMessageBox::warning(nullptr, "Error", "Incorrect password!");
        return false;
    }

    QMessageBox::information(nullptr, "Success", "You have successfully logged in!");
    return true;
}
