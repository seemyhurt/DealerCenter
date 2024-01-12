#include "inputuserdialog.h"
#include "inputvalidatorfactory.h"
#include <QSharedPointer>

QStringList InputUserDialog::_params = {"Phone number", "Last name", "First name", "Patronymic", "Age", "Password"};

InputUserDialog::InputUserDialog(QWidget *pwgt)
    : IInputDialogBase(_params, "Registration", QSharedPointer<UserDataValidatorFactory>::create(), pwgt)
{
}

UserData InputUserDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    return UserData::fromWidgetMap(params);
}

