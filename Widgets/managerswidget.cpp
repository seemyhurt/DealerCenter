#include "managerswidget.h"

#include "purchasewidget.h"
#include "logindialog.h"
#include "transporttablewidget.h"
#include "manufacturerstablewidget.h"

#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

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
    _manufacturersWidget(QSharedPointer<ManufacturersTableWidget>::create(false)),
    _transportsWidget(QSharedPointer<TransportTableWidget>::create())
{
    auto groupPurchase = new QGroupBox("Purchase form: ", this);
    auto groupManufacturers = new QGroupBox("Manufacturers: ", this);
    auto groupTransports = new QGroupBox("Transports: ", this);

    auto purchaseWidget = new PurchaseWidget(this);
    connect(purchaseWidget, &PurchaseWidget::needCreatePurchase, this, &ManagersWidget::handleCreatePurchase);
    auto layout = new QHBoxLayout(this);

    auto layoutManufacturers = new QVBoxLayout(this);
    layoutManufacturers->addWidget(_manufacturersWidget.data());
    groupManufacturers->setLayout(layoutManufacturers);

    auto layoutTransport = new QVBoxLayout(this);
    layoutTransport->addWidget(_transportsWidget.data());
    groupTransports->setLayout(layoutTransport);

    auto layoutLeft = new QVBoxLayout(this);
    layoutLeft->addWidget(groupManufacturers);
    layoutLeft->addWidget(groupTransports);

    groupPurchase->setLayout(purchaseWidget->layout());

    layout->addLayout(layoutLeft, 6);
    layout->addWidget(groupPurchase, 1);
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

void ManagersWidget::handleCreatePurchase()
{

}
