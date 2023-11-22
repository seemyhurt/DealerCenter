#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QVariantMap>

/**
 * @brief Структура пользователя из базы данных.
 * @details Именна соответствуют полям в БД.
 */

struct UserData
{
    int id;                 ///< Идентификатор записи
    quint64 phoneNumber;    ///< Номер телефона
    QString firstName;      ///< Фамилия
    QString lastName;       ///< Имя
    QString surname;        ///< Отчество
    int age;                ///< Возраст
    QString type;           ///< Тип пользователя
    QString password;       ///< Пароль

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"phoneNumber", phoneNumber},
            {"firstName", firstName},
            {"lastName", lastName},
            {"surname", surname},
            {"age", age},
            {"type", type},
            {"password", password}
        };
    }

    static UserData fromDBMap(const QVariantMap &variant)
    {
        UserData temp;
        temp.id = variant.value("id").toInt();
        temp.phoneNumber = variant.value("phoneNumber").toLongLong();
        temp.firstName = variant.value("firstName").toString();
        temp.lastName = variant.value("lastName").toString();
        temp.surname = variant.value("surname").toString();
        temp.age = variant.value("age").toInt();
        temp.type = variant.value("type").toString();
        temp.password = variant.value("password").toString();
        return temp;
    }

    QVariantMap toWidgetMap() const
    {
        return QVariantMap {
            {"ID", id},
            {"Phone number", phoneNumber},
            {"Firstname", firstName},
            {"Lastname", lastName},
            {"Surname", surname},
            {"Age", age},
            {"Type", type},
            {"Password", password}
        };
    }

    static UserData fromWidgetMap(const QVariantMap &variant)
    {
        UserData temp;
        temp.id = variant.value("idr", 0).toLongLong();
        temp.phoneNumber = variant.value("Phone number").toLongLong();
        temp.firstName = variant.value("First name").toString();
        temp.lastName = variant.value("Last name").toString();
        temp.surname = variant.value("Surname").toString();
        temp.age = variant.value("Age").toInt();
        temp.password = variant.value("Password").toString();
        return temp;
    }
};

#endif // USERDATA_H
