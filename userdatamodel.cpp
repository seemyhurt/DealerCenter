#include "userdatamodel.h"
#include "UserData.h"
#include "userdbservice.h"
#include "servicelocator.h"

UserDataModel::UserDataModel(QObject * parent) :
    QObject(parent)
{
    _service = QSharedPointer<UserDBService>::create();
    ServiceLocator::addService(_service);
}

bool UserDataModel::addUser(const UserData &user)
{
    auto temp = user.toDBMap();
    auto err = _service->addEntry(temp);
    if (err.type() == QSqlError::ErrorType::NoError)
        return true;
    else
        return false;
}

bool UserDataModel::isUserExist(quint64 number)
{
    return _service->isUserExist(number);
}

bool UserDataModel::isPasswordCorrect(quint64 number, const QString & password)
{
    return _service->isPasswordCorrect(number, password);
}
