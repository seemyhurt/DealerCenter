#include "inputmanufacturerdialog.h"

QStringList InputManufacturerDialog::_params = {"Name", "Delivery time, days", "Guarantee period, years", "Car brand", "Type"};

InputManufacturerDialog::InputManufacturerDialog(QWidget *pwgt) : IInputDialogBase(_params, pwgt)
{
}

ManufacturerData InputManufacturerDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    return ManufacturerData::fromWidgetMap(params);
}
