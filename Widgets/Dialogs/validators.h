#ifndef VALIDATORS_H
#define VALIDATORS_H
#include <QRegularExpressionValidator>

class NameValidator : public QRegularExpressionValidator
{
public:
    NameValidator(QObject * parent = nullptr);
};

class PhoneNumberValidator : public QRegularExpressionValidator
{
public:
    PhoneNumberValidator(QObject * parent = nullptr);
};

class PasswordValidator : public QRegularExpressionValidator
{
public:
    PasswordValidator(QObject * parent = nullptr);
};

class AgeValidator : public QIntValidator
{
public:
    AgeValidator(QObject * parent = nullptr);
};

class GuaranteeValidator : public QIntValidator
{
public:
    GuaranteeValidator(QObject * parent = nullptr);
};

class DeliveryTimeValidator : public QIntValidator
{
public:
    DeliveryTimeValidator(QObject * parent = nullptr);
};

class PriceValidator : public QIntValidator
{
public:
    PriceValidator(QObject * parent = nullptr);
};

#endif // VALIDATORS_H
