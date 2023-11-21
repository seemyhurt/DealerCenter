#include "inputuserdialog.h"

QStringList InputUserDialog::_params = {"Phone number", "First name", "Last name", "Surname", "Age", "Password"};

InputUserDialog::InputUserDialog(QWidget *pwgt) : IInputDialogBase(_params, pwgt)
{
}

UserData InputUserDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    UserData temp;
    temp.phoneNumber = params.value("Phone number").toLongLong();
    temp.firstName = params.value("First name").toString();
    temp.lastName = params.value("Last name").toString();
    temp.surname = params.value("Surname").toString();
    temp.age = params.value("Age").toInt();
    temp.password = params.value("Password").toString();
    return temp;
}

