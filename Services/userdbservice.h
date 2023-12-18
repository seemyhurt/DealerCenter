#ifndef USERDBSERVICE_H
#define USERDBSERVICE_H

#include "../Providers/localbbstorage.h"
#include "../Common/userdata.h"
#include "ilocaldbservicebase.h"
#include <QSharedPointer>

class UserDBProvider;

class UserDBService : public DatabaseCommon::ILocalDBServiceBase
{
    Q_OBJECT
public:
    explicit UserDBService(QObject *parent = nullptr);

    // ILocalDBServiceBase interface
    quint64 tableSize() const override;
    QSqlError addEntry(QVariantMap &values) override;
    QSqlError removeEntry(quint64 id) override;

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();

    QVariantList getAllCustomers();
    QVariantList getAllManagers();

signals:
    void userAdded(const UserData & data);

public:
    bool isCustomerExist(quint64 number);
    bool isManagerExist(quint64 number);
    bool isUserExist(quint64 number);

    UserData getUserByNumber(quint64 number);
    UserData getUserById(int id);
    bool isPasswordCorrect(quint64 number, const QString & password);

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

private:
    void selectDataFromStorage();

private:
    DatabaseCommon::LocalDBStorage<UserData> _storage;
    QSharedPointer<UserDBProvider> _provider;
    QHash<quint64, UserData> _phoneToUser;
};

#endif // USERDBSERVICE_H
