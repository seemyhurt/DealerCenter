#ifndef INPUTVALIDATORFACTORY_H
#define INPUTVALIDATORFACTORY_H

#include <QString>
#include <QValidator>

class  InputValidatorFactory
{    
public:
    InputValidatorFactory();
    virtual ~InputValidatorFactory() {};

    /**
     * @brief Получение наследника QValidator
     */
    virtual QValidator *getValidator(const QString &key, QObject *parent) = 0;
};

class  UserDataValidatorFactory : public InputValidatorFactory
{
public:
    UserDataValidatorFactory();

    QValidator *getValidator(const QString &key, QObject *parent) override;
};

class ManufacturerDataValidatorFactory : public InputValidatorFactory
{
public:
    ManufacturerDataValidatorFactory();

    QValidator *getValidator(const QString &key, QObject *parent) override;
};

class  LoginDataValidatorFactory : public InputValidatorFactory
{
public:
    LoginDataValidatorFactory();

    QValidator *getValidator(const QString &key, QObject *parent) override;
};

#endif // INPUTVALIDATORFACTORY_H
