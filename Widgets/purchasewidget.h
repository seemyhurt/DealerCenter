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
struct PurchaseData;

enum class WidgetInterface
{
    Manager,
    Customer
};

class PurchaseWidget : public QWidget
{
    Q_OBJECT
public:
    PurchaseWidget(const WidgetInterface interface, QWidget * parent = nullptr);

    void setCurrentUser(quint64 number) { _currentUserNumber = number; };

private slots:
    void handleBrandChanged(const QString &brand);
    void handleTypeChanged(const QString &type);
    void handleManufacturerChanged(const QString &manufacturer);
    void handleConditionChanged(const QString &condition);
    void handleManufacturerAdded(const ManufacturerData & data);
    void handleModelChanged(const QString &model);
    void handleCreatePurchase();
    void handleRecalculatePrice(int);
    void handlePurchaseAdded(const PurchaseData &model);

private:
    QSharedPointer<ManufacturerDBService> _manufacturersService;
    QSharedPointer<UserDBService> _usersService;
    QSharedPointer<TransportDBService> _transportService;
    QSharedPointer<PurchasesDBService> _purchasesService;

    QComboBox * _type;
    QComboBox * _brand;
    QComboBox * _manufacturer;
    QComboBox * _condition;

    QComboBox * _availableModels;
    QComboBox * _availableYears;

    QLineEdit * _model;
    QLineEdit * _price;
    QSpinBox * _count;

    quint64 _currentUserNumber;
};

#endif // PURCHASEWIDGET_H
