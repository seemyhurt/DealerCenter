#ifndef IINPUTDIALOGBASE_H
#define IINPUTDIALOGBASE_H

#include <QDialog>

class QLineEdit;
class QLabel;

class IInputDialogBase : public QDialog
{
    Q_OBJECT

public:
    IInputDialogBase(const QStringList &params, QWidget *pwgt = nullptr);
    ~IInputDialogBase();

protected:
    QVariantMap getVariantData(const QStringList &params);

private:
    QVector<QLineEdit*> _inputWidgets;
    QVector<QLabel*> _labels;
};

#endif // IINPUTDIALOGBASE_H
