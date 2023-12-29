#ifndef INPUTMANUFACTURERDIALOG_H
#define INPUTMANUFACTURERDIALOG_H


#include "../../Common/manufacturerdata.h"
#include "iinputdialogbase.h"
#include <QVariantMap>

class QLineEdit;
class InputManufacturerDialog : public IInputDialogBase
{
    Q_OBJECT

public:
    InputManufacturerDialog(QWidget *pwgt = nullptr);

    ManufacturerData getDialogInfo();

private:
    static QStringList _params;
};

#endif // INPUTMANUFACTURERDIALOG_H
