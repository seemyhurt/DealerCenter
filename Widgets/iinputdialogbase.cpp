#include "iinputdialogbase.h"

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "../inputvalidatorfactory.h"

IInputDialogBase::IInputDialogBase(const QStringList & params, QWidget *pwgt)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{

    auto size = params.size();
    _inputWidgets.reserve(size);
    for (const auto &param : qAsConst(params))
    {
        auto wgt = new QLineEdit(this);
        wgt->setValidator(InputValidatorFactory::validator(param));
        _inputWidgets <<  wgt;

        _labels << new QLabel(QString("&%1: ").arg(param), this);
    }

    QPushButton* pcmdOk = new QPushButton("&Ok", this);
    QPushButton* pcmdCancel = new QPushButton("&Cancel", this);

    connect(pcmdOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(pcmdCancel, &QPushButton::clicked, this,  &QDialog::reject);

    _layout = new QGridLayout(this);
    for (int i = 0; i < size; i++)
    {
        _labels[i]->setBuddy(_inputWidgets[i]);
        _layout->addWidget(_labels[i], i, 0);
        _layout->addWidget(_inputWidgets[i], i, 1);
    }

    _layout->addWidget(pcmdOk, size, 0);
    _layout->addWidget(pcmdCancel, size, 1);

    setLayout(_layout);
}

IInputDialogBase::~IInputDialogBase()
{
    for (const auto widget : qAsConst(_inputWidgets))
        delete widget;

    for (const auto widget : qAsConst(_labels))
        delete widget;
}

QVariantMap IInputDialogBase::getVariantData(const QStringList &params)
{
    if (params.size() > _inputWidgets.size())
        return {};

    QVariantMap result;
    for (int i = 0; i < params.size(); i++)
        result.insert(params[i], _inputWidgets[i]->text());

    return result;
}
