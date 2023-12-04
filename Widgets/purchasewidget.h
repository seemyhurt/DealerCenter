#ifndef PURCHASEWIDGET_H
#define PURCHASEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class ManufacturerDBService;
class UserDBService;
class TransportDBService;
class PurchasesDBService;

class QComboBox;
class QLineEdit;
class QSpinBox;
struct ManufacturerData;

class PurchaseWidget : public QWidget
{
    Q_OBJECT
public:
    PurchaseWidget(QWidget * parent = nullptr);

    void setCurrentUser(quint64 number) { _currentUserNumber = number; };

private:
    void handleBrandChanged(const QString &brand);
    void handleTypeChanged(const QString &brand);
    void handleConditionChanged(const QString &condition);
    void handleManufacturerAdded(const ManufacturerData & data);
    void handleCreatePurchase();

private:
    QSharedPointer<ManufacturerDBService> _manufacturersService;
    QSharedPointer<UserDBService> _usersService;
    QSharedPointer<TransportDBService> _transportService;
    QSharedPointer<PurchasesDBService> _purchasesService;

    QComboBox * _type;
    QComboBox * _brand;
    QComboBox * _manufacturer;
    QComboBox * _condition;
    QLineEdit * _model;
    QLineEdit * _year;
    QSpinBox * _count;

    quint64 _currentUserNumber;
};

#endif // PURCHASEWIDGET_H
