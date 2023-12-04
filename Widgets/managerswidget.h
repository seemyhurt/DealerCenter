#ifndef MANAGERSWIDGET_H
#define MANAGERSWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class ManufacturersTableWidget;
class TransportTableWidget;
class PurchaseWidget;
class PurchasesTableWidget;

class ManagersWidget : public QWidget
{
    Q_OBJECT
public:
    ManagersWidget(QWidget * parent = nullptr);

    bool loginManager();

private:
    QSharedPointer<UserDBService> _service;
    QSharedPointer<ManufacturersTableWidget> _manufacturersWidget;
    QSharedPointer<TransportTableWidget> _transportsWidget;
    QSharedPointer<PurchaseWidget> _purchasesWidget;
    QSharedPointer<PurchasesTableWidget> _purchasesTableWidget;
};

#endif // MANAGERSWIDGET_H
