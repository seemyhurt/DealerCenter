#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class QTabWidget;
class QStandardItemModel;

class CustomersTableWidget;
class ManufacturersTableWidget;
class ManagersTableWidget;

class AdministratorWidget : public QWidget
{
    Q_OBJECT
public:
    AdministratorWidget(QWidget * parent = nullptr);

private:
    QSharedPointer<QTabWidget> _tabs;
    QSharedPointer<CustomersTableWidget> _customersWidget;
    QSharedPointer<ManufacturersTableWidget> _manufacturersWidget;
    QSharedPointer<ManagersTableWidget> _managersWidget;
};

#endif // ADMINISTRATORWIDGET_H
