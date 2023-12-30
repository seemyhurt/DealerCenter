#include "administratorwidget.h"
#include "Dialogs/inputuserdialog.h"
#include "Dialogs/logindialog.h"
#include "customerstablewidget.h"
#include "manufacturerstablewidget.h"
#include "managerstablewidget.h"
#include "transporttablewidget.h"

#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QDialog>
#include <QMessageBox>

AdministratorWidget::AdministratorWidget(QSharedPointer<TransportsModel> transportModel,
                                         QSharedPointer<ManufacturersModel> manufacturerModel,
                                         QWidget *parent)
    : QWidget(parent),
    _tabs(new QTabWidget(this)),
    _customersWidget(new CustomersTableWidget(this)),
    _manufacturersWidget(new ManufacturersTableWidget(manufacturerModel, true, this)),
    _managersWidget(new ManagersTableWidget(this)),
    _transportsWidget(new TransportTableWidget(transportModel, this)),
    _service(ServiceLocator::service<UserDBService>())
{
    _tabs->addTab(_customersWidget, "Customers");
    _tabs->addTab(_manufacturersWidget, "Manufacturers");
    _tabs->addTab(_managersWidget, "Managers");
    _tabs->addTab(_transportsWidget, "Transport");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs);
    setLayout(_tabs->layout());
}

bool AdministratorWidget::loginAdministrator()
{
    if (!_service->isAdministratorExist())
        return registerAdministrator();

    auto dialog = new LoginDialog(false, this);
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto loginInfo = dialog->getDialogInfo();

    if (!_service->isAdministratorExist(loginInfo.first))
    {
        QMessageBox::warning(nullptr, "Error", "Administrator not exists, please try again!");
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

bool AdministratorWidget::registerAdministrator()
{
    auto dialog = new InputUserDialog();
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto user = dialog->getDialogInfo();

    user.type = "Administrator";

    if (!user.isValid())
    {
        QMessageBox::warning(this, "Error", "Wrong user data!");
        return false;
    }

    auto userDbdata = user.toDBMap();

    if (_service->isUserExist(user.phoneNumber))
    {
        QMessageBox::warning(nullptr, "Error", "User with that number already exists!");
        return false;
    }

    if (_service->addEntry(userDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "You have successfully registered!");
        return true;
    }
    else
    {
        QMessageBox::warning(this, "Error", "Incorrect user data");
        return false;
    }
}
