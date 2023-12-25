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
    QString lastName;       ///< Фамилия
    QString firstName;      ///< Имя
    QString patronymic;     ///< Отчество
    int age;                ///< Возраст
    QString type;           ///< Тип пользователя
    QString password;       ///< Пароль

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"phoneNumber", phoneNumber},
            {"lastName", lastName},
            {"firstName", firstName},
            {"patronymic", patronymic},
            {"age", age},
            {"type", type},
            {"password", password}
        };
    }

    static UserData fromDBMap(const QVariantMap &variant)
    {
        UserData temp;
        temp.id = variant.value("id", 0).toInt();
        temp.phoneNumber = variant.value("phoneNumber").toLongLong();
        temp.lastName = variant.value("lastName").toString();
        temp.firstName = variant.value("firstName").toString();
        temp.patronymic = variant.value("patronymic").toString();
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
            {"Last name", lastName},
            {"First name", firstName},
            {"Patronymic", patronymic},
            {"Age", age},
            {"Type", type},
            {"Password", password}
        };
    }

    static UserData fromWidgetMap(const QVariantMap &variant)
    {
        UserData temp;
        temp.id = variant.value("id", 0).toLongLong();
        temp.phoneNumber = variant.value("Phone number").toLongLong();
        temp.lastName = variant.value("Last name").toString();
        temp.firstName = variant.value("First name").toString();
        temp.patronymic = variant.value("Patronymic").toString();
        temp.age = variant.value("Age").toInt();
        temp.password = variant.value("Password").toString();
        return temp;
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"Phone number", "Last name", "First name", "Patronymic", "Age", "Type", "Password"};
    }

    static QStringList dBKeys()
    {
        return QStringList {"id", "phoneNumber", "lastName", "firstName",  "patronymic", "age", "type", "password"};
    }
};

#endif // USERDATA_H
