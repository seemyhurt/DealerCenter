#ifndef USERDBSERVICE_H
#define USERDBSERVICE_H

#include "ilocaldbservicebase.h"
#include "localbbstorage.h"
#include <QSharedPointer>
#include "userdata.h"

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

    QVariantList getAllUsers();

signals:
    void userAdded(const UserData & data);

public:
    bool isUserExist(quint64 number);
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
