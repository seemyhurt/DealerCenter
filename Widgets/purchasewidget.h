#ifndef PURCHASEWIDGET_H
#define PURCHASEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class ManufacturerDBService;
class QComboBox;

class PurchaseWidget : public QWidget
{
public:
    PurchaseWidget(QWidget * parent = nullptr);

private:
    void handleBrandChanged(const QString &brand);

private:
    QSharedPointer<ManufacturerDBService> _service;
    QComboBox * manufacturer;
};

#endif // PURCHASEWIDGET_H
