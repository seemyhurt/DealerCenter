#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class QTabWidget;
class QStandardItemModel;

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
    QSharedPointer<QTabWidget> _tabs;
    QSharedPointer<CustomersTableWidget> _customersWidget;
    QSharedPointer<ManufacturersTableWidget> _manufacturersWidget;
    QSharedPointer<ManagersTableWidget> _managersWidget;
    QSharedPointer<TransportTableWidget> _transportsWidget;
};

#endif // ADMINISTRATORWIDGET_H
