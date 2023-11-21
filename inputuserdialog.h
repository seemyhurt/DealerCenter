#ifndef INPUTUSERDIALOG_H
#define INPUTUSERDIALOG_H

#include "userdata.h"
#include "iinputdialogbase.h"
#include <QVariantMap>

class QLineEdit;
class InputUserDialog : public IInputDialogBase
{
    Q_OBJECT

public:
    InputUserDialog(QWidget *pwgt = nullptr);

    UserData getDialogInfo();

private:
    static QStringList _params;
};

#endif // INPUTUSERDIALOG_H
