#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>
#include <QSharedPointer>


class QTabWidget;
class QStandardItemModel;

class UserDBService;
struct UserData;

class ManufacturerDBService;
struct ManufacturerData;

class AdministratorWidget : public QWidget
{
    Q_OBJECT
public:
    AdministratorWidget(QWidget * parent = nullptr);

private:
    void initCustomersWidget();
    void initManufacturersWidget();

private slots:
    void handleNeedUpdateCustomers(const UserData& data);
    void handleNeedUpdateManufacturers(const ManufacturerData& data);

    void handleNeedAddManufacturer();

private:
    QSharedPointer<QTabWidget> _tabs;
    QSharedPointer<UserDBService> _userService;
    QSharedPointer<QWidget> _customersWidget;
    QSharedPointer<QStandardItemModel> _customerModel;

    QSharedPointer<ManufacturerDBService> _manufacturersService;
    QSharedPointer<QWidget> _manufacturersWidget;
    QSharedPointer<QStandardItemModel> _manufacturersModel;
};

#endif // ADMINISTRATORWIDGET_H
