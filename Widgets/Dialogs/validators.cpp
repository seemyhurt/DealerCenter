#include "validators.h"
#include <QRegularExpression>

static QRegularExpression nameRegExp("^[A-ZА-Я][a-zа-я]{0,29}$");
static QRegularExpression phoneRegExp("^8[0-9]{10}$");
static QRegularExpression passwordRegExp("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");

NameValidator::NameValidator(QObject *parent) : QRegularExpressionValidator(nameRegExp, parent)
{
}

PhoneNumberValidator::PhoneNumberValidator(QObject *parent) : QRegularExpressionValidator(phoneRegExp, parent)
{

}

PasswordValidator::PasswordValidator(QObject *parent) : QRegularExpressionValidator(passwordRegExp, parent)
{

}


AgeValidator::AgeValidator(QObject *parent) : QIntValidator(parent)
{
    setRange(10, 99);
}


GuaranteeValidator::GuaranteeValidator(QObject *parent) : QIntValidator(parent)
{
    setRange(0, 50);
}

DeliveryTimeValidator::DeliveryTimeValidator(QObject *parent) : QIntValidator(parent)
{
    setRange(0, 30);
}

PriceValidator::PriceValidator(QObject *parent) : QIntValidator(parent)
{
    setRange(0, 999999);
}
