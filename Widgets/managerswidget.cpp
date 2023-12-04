#include "managerswidget.h"

#include "purchasewidget.h"
#include "logindialog.h"
#include "transporttablewidget.h"
#include "manufacturerstablewidget.h"
#include "purchasestablewidget.h"

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
    _transportsWidget(QSharedPointer<TransportTableWidget>::create()),
    _purchasesWidget(QSharedPointer<PurchaseWidget>::create(this)),
    _purchasesTableWidget(QSharedPointer<PurchasesTableWidget>::create(this))
{
    auto groupPurchase = new QGroupBox("Purchase form: ", this);
    auto groupManufacturers = new QGroupBox("Manufacturers: ", this);
    auto groupTransports = new QGroupBox("Transports: ", this);
    auto groupPurchases = new QGroupBox("My purchases: ", this);

    auto layout = new QHBoxLayout(this);

    auto layoutManufacturers = new QVBoxLayout(this);
    layoutManufacturers->addWidget(_manufacturersWidget.data());
    groupManufacturers->setLayout(layoutManufacturers);

    auto layoutTransport = new QVBoxLayout(this);
    layoutTransport->addWidget(_transportsWidget.data());
    groupTransports->setLayout(layoutTransport);

    auto layoutPurchase = new QVBoxLayout(this);
    layoutPurchase->addWidget(_purchasesTableWidget.data());
    groupPurchases->setLayout(layoutPurchase);

    auto layoutLeft = new QVBoxLayout(this);
    layoutLeft->addWidget(groupManufacturers);
    layoutLeft->addWidget(groupTransports);

    auto layoutRight = new QVBoxLayout(this);
    layoutRight->addWidget(groupPurchase);
    layoutRight->addWidget(groupPurchases);

    groupPurchase->setLayout(_purchasesWidget.data()->layout());

    layout->addLayout(layoutLeft, 6);
    layout->addLayout(layoutRight, 3);
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
    _purchasesWidget->setCurrentUser(loginInfo.first);
    return true;
}
