#ifndef USERDATAMODEL_H
#define USERDATAMODEL_H

#include <QObject>
#include <QSharedPointer>

class UserDBService;
struct UserData;

class UserDataModel : public QObject
{
    Q_OBJECT

public:
    UserDataModel(QObject * parent = nullptr);

    bool isUserExist(quint64 number);
    bool isPasswordCorrect(quint64 number, const QString & password);

    bool addUser(const UserData &user);

private:
    QSharedPointer<UserDBService> _service;
};

#endif // USERDATAMODEL_H
