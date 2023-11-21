#include "customerwidget.h"
#include "inputuserdialog.h"
#include "inputnumberdialog.h"
#include "servicelocator.h"
#include "userdbservice.h"

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
    auto dialog = new InputNumberDialog(this);
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto phoneNumber = dialog->getDialogInfo();

    if (!_service->isUserExist(phoneNumber))
        return registerUser();

    QString password = QInputDialog::getText(nullptr, "Enter password", "Password:");
    if (!_service->isPasswordCorrect(phoneNumber, password))
    {
        QMessageBox::warning(nullptr, "Error", "Incorrect password!");
        return false;
    }

    QMessageBox::information(nullptr, "Success", "You have successfully logged in!");
    return true;
}

bool CustomerWidget::registerUser()
{
    auto dialog = new InputUserDialog();
    if (dialog->exec() != QDialog::Accepted)
        return false;

    auto user = dialog->getDialogInfo();
    delete dialog;

    user.type = "Customer";
    auto userDbdata = user.toDBMap();
    if (_service->addEntry(userDbdata).type() == QSqlError::NoError)
    {
        QMessageBox::information(this, "Successfully added", "You have successfully registered!");
        return true;
    }

    QMessageBox::warning(nullptr, "Error", "Incorrect user data");
    return false;


}
