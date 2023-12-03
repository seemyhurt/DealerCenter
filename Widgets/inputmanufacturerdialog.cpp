#include "inputmanufacturerdialog.h"

QStringList InputManufacturerDialog::_params = {"Name", "Delivery time, days", "Guarantee period, years", "Transport brand", "Transport type"};

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
