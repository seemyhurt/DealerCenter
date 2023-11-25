#ifndef MANAGERSTABLEWIDGET_H
#define MANAGERSTABLEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class QStandardItemModel;
class UserDBService;
struct UserData;

class ManagersTableWidget : public QWidget
{
    Q_OBJECT
public:
    ManagersTableWidget(QWidget * parent = nullptr);

private slots:
    void handleNeedUpdateManagers(const UserData& data);
    void handleNeedAddManager();

private:
    QSharedPointer<UserDBService> _usersService;
    QSharedPointer<QStandardItemModel> _managersModel;
};

#endif // MANAGERSTABLEWIDGET_H
