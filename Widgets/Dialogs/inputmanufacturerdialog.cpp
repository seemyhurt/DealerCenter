#include "inputmanufacturerdialog.h"
#include "inputvalidatorfactory.h"
#include <QSharedPointer>

QStringList InputManufacturerDialog::_params = {"Name", "Delivery time, days", "Guarantee period, years", "Transport brand", "Transport type", "Base price"};

InputManufacturerDialog::InputManufacturerDialog(QWidget *pwgt) :
    IInputDialogBase(_params, "Manufacturer", QSharedPointer<ManufacturerDataValidatorFactory>::create(), pwgt)
{

}

ManufacturerData InputManufacturerDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    return ManufacturerData::fromWidgetMap(params);
}
