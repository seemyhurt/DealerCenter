#ifndef IINPUTDIALOGBASE_H
#define IINPUTDIALOGBASE_H

#include <QDialog>

class QLineEdit;
class QLabel;
class QGridLayout;
class InputValidatorFactory;

class IInputDialogBase : public QDialog
{
    Q_OBJECT

public:
    IInputDialogBase(const QStringList &params,
                     const QString &dialogName,
                     QSharedPointer<InputValidatorFactory> factory,
                     QWidget *pwgt = nullptr);

    ~IInputDialogBase();

protected:
    QVariantMap getVariantData(const QStringList &params);

    QGridLayout * currentLayout() { return _layout; };

private:
    QVector<QLineEdit*> _inputWidgets;
    QVector<QLabel*> _labels;
    QGridLayout * _layout;
};

#endif // IINPUTDIALOGBASE_H
