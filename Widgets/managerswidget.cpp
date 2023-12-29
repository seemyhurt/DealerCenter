#include "managerswidget.h"

#include "Dialogs/logindialog.h"

#include "purchasewidget.h"
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

ManagersWidget::ManagersWidget(QSharedPointer<PurchasesModel> purchasesModel,
                               QSharedPointer<TransportsModel> transportsModel,
                               QSharedPointer<ManufacturersModel> manufacturersModel,
                               QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>()),
    _manufacturersWidget(new ManufacturersTableWidget(manufacturersModel, false)),
    _transportsWidget(new TransportTableWidget(transportsModel)),
    _purchasesWidget(new PurchaseWidget(WidgetInterface::Manager, this)),
    _purchasesTableWidget(new PurchasesTableWidget(purchasesModel, this))
{
    auto groupPurchase = new QGroupBox("Purchase form: ", this);
    auto groupManufacturers = new QGroupBox("Manufacturers: ", this);
    auto groupTransports = new QGroupBox("Transports: ", this);
    auto groupPurchases = new QGroupBox("My purchases: ", this);

    auto layout = new QHBoxLayout(this);

    auto layoutManufacturers = new QVBoxLayout(this);
    layoutManufacturers->addWidget(_manufacturersWidget);
    groupManufacturers->setLayout(layoutManufacturers);

    auto layoutTransport = new QVBoxLayout(this);
    layoutTransport->addWidget(_transportsWidget);
    groupTransports->setLayout(layoutTransport);

    auto layoutPurchase = new QVBoxLayout(this);
    layoutPurchase->addWidget(_purchasesTableWidget);
    groupPurchases->setLayout(layoutPurchase);

    auto layoutLeft = new QVBoxLayout(this);
    layoutLeft->addWidget(groupManufacturers);
    layoutLeft->addWidget(groupTransports);

    auto layoutRight = new QVBoxLayout(this);
    layoutRight->addWidget(groupPurchase);
    layoutRight->addWidget(groupPurchases);

    groupPurchase->setLayout(_purchasesWidget->layout());

    layout->addLayout(layoutLeft, 8);
    layout->addLayout(layoutRight, 3);
    setLayout(layout);
}

bool ManagersWidget::loginManager()
{
    auto dialog = new LoginDialog(false, this);
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto loginInfo = dialog->getDialogInfo();

    if (!_service->isManagerExist(loginInfo.first))
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
    _purchasesTableWidget->setCurrentUser(loginInfo.first);
    return true;
}
