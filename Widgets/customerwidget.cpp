#include "customerwidget.h"
#include "inputuserdialog.h"
#include "logindialog.h"
#include "../Services/servicelocator.h"
#include "../Services/userdbservice.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlError>

CustomerWidget::CustomerWidget(QWidget *parent)
    : QWidget(parent),
    _service(ServiceLocator::service<UserDBService>())
{
    QLabel *titleLabel = new QLabel("Форма покупки автомобиля", this);

    QLabel *carLabel = new QLabel("Выберите автомобиль:", this);
    QComboBox *carComboBox = new QComboBox(this);
    carComboBox->addItem("Модель 1");
    carComboBox->addItem("Модель 2");
    carComboBox->addItem("Модель 3");

    QLabel *priceLabel = new QLabel("Цена:", this);
    QLineEdit *priceLineEdit = new QLineEdit(this);

    QPushButton *buyButton = new QPushButton("Купить", this);

    // Размещение виджетов на форме
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(carLabel);
    layout->addWidget(carComboBox);
    layout->addWidget(priceLabel);
    layout->addWidget(priceLineEdit);
    layout->addWidget(buyButton);
    setLayout(layout);
}

bool CustomerWidget::loginCutomer()
{
    auto dialog = new LoginDialog(true, this);
    connect(dialog, &LoginDialog::needRegister, this, &CustomerWidget::handleRegisterUser);

    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto loginInfo = dialog->getDialogInfo();

    if (!_service->isUserExist(loginInfo.first))
    {
        QMessageBox::warning(this, "Error", "User with that number not exists!");
        return false;
    }
    if (!_service->isPasswordCorrect(loginInfo.first, loginInfo.second))
    {
        QMessageBox::warning(this, "Error", "Wrong password!");
        return false;
    }

    QMessageBox::information(this, "Success", "You have successfully logged in!");
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

    if (_service->addEntry(userDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "You have successfully registered!");
        emit newUserRegistred();
    }
    else
        QMessageBox::warning(this, "Error", "Incorrect user data");
}
