#ifndef INPUTNUMBERDIALOG_H
#define INPUTNUMBERDIALOG_H

#include "iinputdialogbase.h"
#include <QVariantMap>

class QLineEdit;
class InputNumberDialog : public IInputDialogBase
{
    Q_OBJECT

public:
    InputNumberDialog(QWidget *pwgt = 0);

    quint64 getDialogInfo();

private:
    static QStringList _params;
};

#endif // INPUTNUMBERDIALOG_H
