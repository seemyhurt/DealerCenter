#include "inputvalidatorfactory.h"

InputValidatorFactory::InputValidatorFactory()
{

}

QValidator * InputValidatorFactory::validator(const QString &key, QObject * parent)
{
    static QRegularExpression nameRegExp("^[A-ZА-Я][a-zа-я]{0,29}$");
    static QRegularExpression phoneRegExp("^8[0-9]{10}$");
    static QRegularExpression passwordRegExp("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");

    if (key == QLatin1String("Last name"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("First name"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("Patronymic"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("Age"))
        return new QIntValidator(10, 99, parent);
    if (key == QLatin1String("Phone number"))
        return new QRegularExpressionValidator(phoneRegExp, parent);
    if (key == QLatin1String("Password"))
        return new QRegularExpressionValidator(passwordRegExp, parent);

    if (key == QLatin1String("Name"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("Delivery time, days"))
        return new QIntValidator(1, 99, parent);
    if (key == QLatin1String("Guarantee period, years"))
        return new QIntValidator(0, 9, parent);
    if (key == QLatin1String("Transport brand"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("Transport type"))
        return new QRegularExpressionValidator(nameRegExp, parent);
    if (key == QLatin1String("Base price"))
        return new QIntValidator(0, 999999999, parent);
}
