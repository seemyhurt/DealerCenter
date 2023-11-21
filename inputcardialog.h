#ifndef INPUTCARDIALOG_H
#define INPUTCARDIALOG_H

#include "transportdata.h"
#include "iinputdialogbase.h"
#include <QVariantMap>

class QLineEdit;
class InputCarDialog : public IInputDialogBase
{
    Q_OBJECT

public:
    InputCarDialog(QWidget *pwgt = 0);

    TransportData getDialogInfo();

private:
    static QStringList _params;
};

#endif // INPUTCARDIALOG_H
