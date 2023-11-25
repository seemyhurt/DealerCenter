#ifndef CUSTOMERSTABLEWIDGET_H
#define CUSTOMERSTABLEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class QStandardItemModel;
class UserDBService;
struct UserData;

class CustomersTableWidget : public QWidget
{
    Q_OBJECT
public:
    CustomersTableWidget(QWidget * parent = nullptr);

private slots:
    void handleNeedUpdateCustomers(const UserData& data);

private:
    QSharedPointer<UserDBService> _userService;
    QSharedPointer<QStandardItemModel> _customerModel;
};

#endif // CUSTOMERSTABLEWIDGET_H
