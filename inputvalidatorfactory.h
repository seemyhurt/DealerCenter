#ifndef INPUTVALIDATORFACTORY_H
#define INPUTVALIDATORFACTORY_H

#include <QString>
#include <QValidator>
#include <QSharedPointer>

class  InputValidatorFactory
{
    InputValidatorFactory();

public:
    ~InputValidatorFactory();

    /**
     * @brief Получение наследника QValidator
     */
    static QValidator *validator(const QString &key);

private:
    static InputValidatorFactory _validatorFactory;
};

#endif // INPUTVALIDATORFACTORY_H
