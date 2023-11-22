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

    return UserData::fromWidgetMap(params);
}

