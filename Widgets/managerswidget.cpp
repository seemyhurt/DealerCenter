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
#include <QGroupBox>

ManagersWidget::ManagersWidget(QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>()),
    _manufacturersModel(QSharedPointer<ManufacturersModel>::create())
{
    auto groupPurchase = new QGroupBox("Purchase form: ", this);

    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->verticalHeader()->setVisible(false);
    tableView->setModel(_manufacturersModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto purchaseWidget = new PurchaseWidget(this);
    connect(purchaseWidget, &PurchaseWidget::needCreatePurchase, this, &ManagersWidget::handleCreatePurchase);
    auto layout = new QVBoxLayout(this);

    groupPurchase->setLayout(purchaseWidget->layout());

    layout->addWidget(tableView);
    layout->addWidget(groupPurchase);
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

    else if (!_service->isPasswordCorrect(loginInfo.first, loginInfo.second))
    {
        QMessageBox::warning(nullptr, "Error", "Incorrect password!");
        return false;
    }

    QMessageBox::information(nullptr, "Success", "You have successfully logged in!");
    return true;
}
