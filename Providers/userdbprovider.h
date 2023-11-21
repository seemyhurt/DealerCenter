#ifndef USERDBPROVIDER_H
#define USERDBPROVIDER_H

#include "localdbproviderbase.h"

struct UserData;
/**
 * @brief Провайдер БД пользователей.
 */
class UserDBProvider
    : public DatabaseCommon::LocalDBProviderBase
{
    Q_OBJECT

public:
    /**
     * @brief Default конструктор.
     * @param parent Родитель.
     */
    explicit UserDBProvider(QObject* parent = nullptr);

    /**
     * @brief Метод доступа к пользователям из БД.
     * @return Массив пользователей.
     */
    QVector<UserData> getUsers();

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();
};

#endif // USERDBPROVIDER_H
