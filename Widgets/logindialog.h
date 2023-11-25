#ifndef LoginDialog_H
#define LoginDialog_H

#include "iinputdialogbase.h"
#include <QVariantMap>

class QLineEdit;
class LoginDialog : public IInputDialogBase
{
    Q_OBJECT

public:
    LoginDialog(bool enableRegister = false, QWidget *pwgt = 0);

    std::pair<quint64, QString> getDialogInfo();

signals:
    void needRegister();

private:
    static QStringList _params;
};

#endif // LoginDialog_H
