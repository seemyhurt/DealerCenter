#ifndef MANAGERSWIDGET_H
#define MANAGERSWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class ManufacturersTableWidget;
class TransportTableWidget;
class PurchaseWidget;
class PurchasesTableWidget;
class PurchasesModel;
class TransportsModel;
class ManufacturersModel;

class ManagersWidget : public QWidget
{
    Q_OBJECT
public:
    ManagersWidget(QSharedPointer<PurchasesModel> purchasesModel,
                   QSharedPointer<TransportsModel> transportsModel,
                   QSharedPointer<ManufacturersModel> manufacturersModel,
                   QWidget *parent = nullptr);

    bool loginManager();

private:
    QSharedPointer<UserDBService> _service;
    ManufacturersTableWidget * _manufacturersWidget;
    TransportTableWidget * _transportsWidget;
    PurchaseWidget * _purchasesWidget;
    PurchasesTableWidget * _purchasesTableWidget;
};

#endif // MANAGERSWIDGET_H
