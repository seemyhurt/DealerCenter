#ifndef ADMINISTRATORWIDGET_H
#define ADMINISTRATORWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class QTabWidget;
class QStandardItemModel;
struct UserData;

class AdministratorWidget : public QWidget
{
    Q_OBJECT
public:
    AdministratorWidget(QWidget * parent = nullptr);

private:
    void initCustomersWidget();

private slots:
    void handleNeedUpdateCustomers(const UserData& data);

private:
    QSharedPointer<UserDBService> _service;
    QSharedPointer<QTabWidget> _tabs;
    QSharedPointer<QWidget> _customersWidget;
    QSharedPointer<QStandardItemModel> _customerModel;
};

#endif // ADMINISTRATORWIDGET_H
