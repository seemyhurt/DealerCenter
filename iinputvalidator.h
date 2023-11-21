#ifndef IINPUTVALIDATOR_H
#define IINPUTVALIDATOR_H

#include <QSharedPointer>

class QValidator;

class IInputValidator
{
public:
    IInputValidator();

    QSharedPointer<QValidator> validator() {return _validator;};

private:
    QSharedPointer<QValidator> _validator;
};

#endif // IINPUTVALIDATOR_H
