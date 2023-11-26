#ifndef PURCHASEWIDGET_H
#define PURCHASEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class ManufacturerDBService;
class QComboBox;
class QLineEdit;
struct ManufacturerData;

class PurchaseWidget : public QWidget
{
public:
    PurchaseWidget(QWidget * parent = nullptr);

private:
    void handleBrandChanged(const QString &brand);
    void handleConditionChanged(const QString &condition);
    void handleManufacturerAdded(const ManufacturerData & data);

private:
    QSharedPointer<ManufacturerDBService> _service;
    QComboBox * manufacturer;
    QComboBox * brand;
    QComboBox * condition;
    QLineEdit * year;
};

#endif // PURCHASEWIDGET_H
