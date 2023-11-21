#include "inputnumberdialog.h"

QStringList InputNumberDialog::_params = {"Phone number"};

InputNumberDialog::InputNumberDialog(QWidget *pwgt) : IInputDialogBase(_params, pwgt)
{
}

quint64 InputNumberDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    return params.value("Phone number").toLongLong();
}

