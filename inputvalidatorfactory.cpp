#include "inputvalidatorfactory.h"

InputValidatorFactory::InputValidatorFactory()
{

}

QValidator * InputValidatorFactory::validator(const QString &key)
{
    static QRegularExpression nameRegExp("^[A-ZА-Я][a-zа-я]{0,29}$");
    static QRegularExpression ageRegExp("[1-9][0-9]$");
    static QRegularExpression phoneRegExp("^8[0-9]{10}$");
    static QRegularExpression passwordRegExp("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");

//    if (key == QLatin1String("First name"))
//        return QSharedPointer<QRegularExpressionValidator>::create(nameRegExp);
//    if (key == QLatin1String("Last name"))
//        return QSharedPointer<QRegularExpressionValidator>::create(nameRegExp);
//    if (key == QLatin1String("Surname"))
//        return QSharedPointer<QRegularExpressionValidator>::create(nameRegExp);
//    if (key == QLatin1String("Surname"))
//        return QSharedPointer<QRegularExpressionValidator>::create(nameRegExp);
//    if (key == QLatin1String("Age"))
//        return QSharedPointer<QRegularExpressionValidator>::create(ageRegExp);
    if (key == QLatin1String("Phone number"))
        return new QRegularExpressionValidator(phoneRegExp);
//    if (key == QLatin1String("Password"))
//        return QSharedPointer<QRegularExpressionValidator>::create(passwordRegExp);
}
