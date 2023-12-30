#include "userdbservice.h"
#include "../Providers/userdbprovider.h"
#include <QDebug>

UserDBService::UserDBService(QObject *parent) :
    ILocalDBServiceBase(parent),
    _provider(QSharedPointer<UserDBProvider>::create())
{
    if(!_provider)
        qDebug() << "Provider is null";

    connect(_provider.data(), &UserDBProvider::dbConnectionChanged,
            this, &UserDBService::handleDbConnectionChange);

    handleDbConnectionChange(_provider->status());
}

quint64 UserDBService::tableSize() const
{
    return _storage.size();
}

QSqlError UserDBService::addEntry(QVariantMap &values)
{
    auto data = UserData::fromDBMap(values);

    auto id = _storage.maxId() + 1;
    values["id"] = id;
    data.id = id;

    _phoneToUser.insert(data.phoneNumber, data);

    auto err = _storage.addEntry(_provider.data(), values, data);
    if (err.type() == QSqlError::NoError)
        emit userAdded(data);
    return err;
}

QSqlError UserDBService::removeEntry(quint64 id)
{
    return _storage.removeEntry(_provider.data(), id);
}

bool UserDBService::isCustomerExist(quint64 number)
{
    return _phoneToUser.contains(number) &&
        _phoneToUser[number].type == QLatin1String("Customer");
}

bool UserDBService::isManagerExist(quint64 number)
{
    return _phoneToUser.contains(number) &&
           _phoneToUser[number].type == QLatin1String("Manager");
}

bool UserDBService::isUserExist(quint64 number)
{
    return _phoneToUser.contains(number);
}

bool UserDBService::isAdministratorExist(quint64 number)
{
    if (number != 0)
        return _phoneToUser.contains(number) &&
               _phoneToUser[number].type == QLatin1String("Administrator");

    for (const auto &user : qAsConst(_storage.elements()))
    {
        if (user.type == QLatin1String("Administrator"))
            return true;
    }
    return false;
}

UserData UserDBService::getUserByNumber(quint64 number)
{
    return _phoneToUser.value(number);
}

UserData UserDBService::getUserById(int id)
{
    return _storage.elements().value(id);
}

bool UserDBService::isPasswordCorrect(quint64 number, const QString & password)
{
    return _phoneToUser[number].password == password;
}

void UserDBService::handleDbConnectionChange(DatabaseCommon::LocalDBStatus status)
{
    _storage.clear();

    if (status != DatabaseCommon::LocalDBStatus::Connected)
        return;

    if (!_provider)
        return;

    _storage.constructElements(_provider->getUsers());
    selectDataFromStorage();
}

void UserDBService::selectDataFromStorage()
{
    for (const auto & element : qAsConst(_storage.elements()))
        _phoneToUser.insert(element.phoneNumber, element);
}

QVector<UserData> UserDBService::getAllCustomers()
{
    QVector<UserData> result;
    result.reserve(_storage.size());
    for (const auto & element : qAsConst(_storage.elements()))
    {
        if (element.type != QLatin1String("Customer"))
            continue;
        result << element;
    }
    return result;
}

QVector<UserData> UserDBService::getAllManagers()
{
    QVector<UserData> result;
    result.reserve(_storage.size());
    for (const auto & element : qAsConst(_storage.elements()))
    {
        if (element.type != QLatin1String("Manager"))
            continue;
        result << element;
    }
    return result;
}

QString UserDBService::baseKey()
{
    return "UserDBService";
}



