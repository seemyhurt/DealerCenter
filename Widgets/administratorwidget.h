#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class QTabWidget;

class CustomersTableWidget;
class ManufacturersTableWidget;
class ManagersTableWidget;
class TransportTableWidget;
class TransportsModel;
class ManufacturersModel;

class AdministratorWidget : public QWidget
{
    Q_OBJECT
public:
    AdministratorWidget(QSharedPointer<TransportsModel> transportModel,
                        QSharedPointer<ManufacturersModel> manufacturerModel,
                        QWidget * parent = nullptr);

private:
    QTabWidget * _tabs;
    CustomersTableWidget * _customersWidget;
    ManufacturersTableWidget * _manufacturersWidget;
    ManagersTableWidget * _managersWidget;
    TransportTableWidget * _transportsWidget;
};

#endif // ADMINISTRATORWIDGET_H
