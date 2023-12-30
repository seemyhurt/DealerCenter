#include "logindialog.h"
#include <QPushButton>
#include <QLayout>

QStringList LoginDialog::_params = {"Phone number", "Password"};

LoginDialog::LoginDialog(bool enableRegister, QWidget *pwgt) : IInputDialogBase(_params, "Authorization", pwgt)
{
    if (!enableRegister)
        return;

    QPushButton* pcmdReg = new QPushButton("&New user");
    currentLayout()->addWidget(pcmdReg, _params.size() + 1, 0, 1, 2);

    connect(pcmdReg, &QPushButton::clicked, this,  &LoginDialog::reject);
    connect(pcmdReg, &QPushButton::clicked, this, &LoginDialog::needRegister);
}

std::pair<quint64, QString> LoginDialog::getDialogInfo()
{
    auto params = getVariantData(_params);
    if(params.isEmpty())
        return {};

    auto number = params.value("Phone number").toLongLong();
    auto password = params.value("Password").toString();
    return std::make_pair(number, password);
}

