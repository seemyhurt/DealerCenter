#include "inputmanufacturerdialog.h"

QStringList InputManufacturerDialog::_params = {"Name", "Delivery time", "Guarantee period", "Car brand"};

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
