#include "customerwidget.h"
#include "Dialogs/inputuserdialog.h"
#include "Dialogs/logindialog.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"
#include "purchasewidget.h"
#include "transporttablewidget.h"
#include "purchasestablewidget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QGroupBox>

CustomerWidget::CustomerWidget(QSharedPointer<TransportsModel> transportModel,
                               QSharedPointer<PurchasesModel> purchaseModel,
                               QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>()),
    _transportsWidget(new TransportTableWidget(transportModel, this)),
    _purchasesWidget(new PurchaseWidget(WidgetInterface::Customer, this)),
    _purchasesTableWidget(new PurchasesTableWidget(purchaseModel, this))
{
    auto groupPurchase = new QGroupBox("Purchase form: ", this);
    auto groupTransports = new QGroupBox("Transports: ", this);
    auto groupPurchases = new QGroupBox("My purchases: ", this);

    auto layout = new QHBoxLayout(this);

    auto layoutTransport = new QVBoxLayout(this);
    layoutTransport->addWidget(_transportsWidget);
    groupTransports->setLayout(layoutTransport);

    auto layoutPurchase = new QVBoxLayout(this);
    layoutPurchase->addWidget(_purchasesTableWidget);
    groupPurchases->setLayout(layoutPurchase);

    auto layoutLeft = new QVBoxLayout(this);
    layoutLeft->addWidget(groupTransports);

    auto layoutRight = new QVBoxLayout(this);
    layoutRight->addWidget(groupPurchase);
    layoutRight->addWidget(groupPurchases);

    groupPurchase->setLayout(_purchasesWidget->layout());

    layout->addLayout(layoutLeft, 8);
    layout->addLayout(layoutRight, 3);
    setLayout(layout);
}

bool CustomerWidget::loginCutomer()
{
    auto dialog = new LoginDialog(true, this);
    connect(dialog, &LoginDialog::needRegister, this, &CustomerWidget::handleRegisterUser);

    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto loginInfo = dialog->getDialogInfo();

    if (!_service->isCustomerExist(loginInfo.first))
    {
        QMessageBox::warning(this, "Error", "User with that number not exists!");
        return false;
    }
    else if (!_service->isPasswordCorrect(loginInfo.first, loginInfo.second))
    {
        QMessageBox::warning(this, "Error", "Wrong password!");
        return false;
    }

    QMessageBox::information(this, "Success", "You have successfully logged in!");
    _purchasesWidget->setCurrentUser(loginInfo.first);
    _purchasesTableWidget->setCurrentUser(loginInfo.first);
    return true;
}

void CustomerWidget::handleRegisterUser()
{
    auto dialog = new InputUserDialog();
    if (dialog->exec() != QDialog::Accepted)
        return;

    auto user = dialog->getDialogInfo();

    user.type = "Customer";
    auto userDbdata = user.toDBMap();

    if (_service->isUserExist(user.phoneNumber))
    {
        QMessageBox::warning(nullptr, "Error", "User with that number already exists!");
        return;
    }

    if (_service->addEntry(userDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "You have successfully registered!");
        emit newUserRegistred();
        _purchasesWidget->setCurrentUser(user.phoneNumber);
        _purchasesTableWidget->setCurrentUser(user.phoneNumber);
    }
    else
        QMessageBox::warning(this, "Error", "Incorrect user data");
}
