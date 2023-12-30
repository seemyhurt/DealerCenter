#include "inputuserdialog.h"

QStringList InputUserDialog::_params = {"Phone number", "Last name", "First name", "Patronymic", "Age", "Password"};

InputUserDialog::InputUserDialog(QWidget *pwgt) : IInputDialogBase(_params, "Registration", pwgt)
{
}

UserData InputUserDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    return UserData::fromWidgetMap(params);
}

