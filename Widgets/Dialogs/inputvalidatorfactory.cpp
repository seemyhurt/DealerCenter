#include "inputvalidatorfactory.h"
#include "validators.h"

InputValidatorFactory::InputValidatorFactory()
{

}

UserDataValidatorFactory::UserDataValidatorFactory()
    : InputValidatorFactory()
{

}

ManufacturerDataValidatorFactory::ManufacturerDataValidatorFactory()
    : InputValidatorFactory()
{

}


LoginDataValidatorFactory::LoginDataValidatorFactory()
    : InputValidatorFactory()
{

}


QValidator * LoginDataValidatorFactory::getValidator(const QString &key, QObject * parent)
{
    if (key == QLatin1String("Phone number"))
        return new PhoneNumberValidator(parent);
    if (key == QLatin1String("Password"))
        return new PasswordValidator(parent);
    return {};
}

QValidator * ManufacturerDataValidatorFactory::getValidator(const QString &key, QObject * parent)
{
    if (key == QLatin1String("Name"))
        return new NameValidator(parent);
    if (key == QLatin1String("Delivery time, days"))
        return new DeliveryTimeValidator(parent);
    if (key == QLatin1String("Guarantee period, years"))
        return new GuaranteeValidator(parent);
    if (key == QLatin1String("Transport brand"))
        return new NameValidator(parent);
    if (key == QLatin1String("Transport type"))
        return new NameValidator(parent);
    if (key == QLatin1String("Base price"))
        return new PriceValidator(parent);
    return {};
}

QValidator * UserDataValidatorFactory::getValidator(const QString &key, QObject * parent)
{
    if (key == QLatin1String("Last name"))
        return new NameValidator(parent);
    if (key == QLatin1String("First name"))
        return new NameValidator(parent);
    if (key == QLatin1String("Patronymic"))
        return new NameValidator(parent);
    if (key == QLatin1String("Age"))
        return new AgeValidator(parent);
    if (key == QLatin1String("Phone number"))
        return new PhoneNumberValidator(parent);
    if (key == QLatin1String("Password"))
        return new PasswordValidator(parent);
    return {};
}

