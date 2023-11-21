#include "inputcardialog.h"

QStringList InputCarDialog::_params = {"Brand", "Model", "Price", "Year"};

InputCarDialog::InputCarDialog(QWidget *pwgt) : IInputDialogBase(_params, pwgt)
{
}

TransportData InputCarDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    TransportData temp;
    temp.brand = params.value("Brand").toString();
    temp.model = params.value("Model").toString();
    temp.price = params.value("Price").toInt();
    temp.year = params.value("Year").toInt();
    return temp;
}
