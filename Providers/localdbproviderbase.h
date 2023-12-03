#ifndef LOCALDBPROVIDERBASE_H
#define LOCALDBPROVIDERBASE_H

#include "iprovider.h"
#include <array>

#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>

namespace DatabaseCommon {

/**
 * @brief Структура описания колонки БД.
 */
struct LocalDBColumn
{
    QString name = "";           ///< Имя колонки
    QString defaultValue = "";   ///< Значение по умолчанию, пустая строка, если значения нету
};

/**
 * @brief Состояние подключения БД.
 */
enum class LocalDBStatus
{
    Unknown,            ///< Неизвестный статус.
    Connected,          ///< БД подключена.
    Unconnected,        ///< БД не подключена.
    FailedConnection    ///< Подключение к БД провалилось.
};

/**
 * @brief Преобразовать статус БД в строку.
 * @param status Статус БД.
 * @return Строка описания статуса.
 */
QString localDBStatusToStr(LocalDBStatus status);

/**
 * @brief Базовый класс провайдера БД.
 */

class LocalDBProviderBase
    : public IProvider
{
    Q_OBJECT

public:
    /**
     * @brief Default конструктор.
     * @param parent Родитель.
     */
    explicit LocalDBProviderBase(QObject* parent = nullptr);
    ~LocalDBProviderBase() override;

    /**
     * @brief Установить имя базы данных для подключения.
     * @details Будет издан сигнал `dbConnectionChanged` с новым статусом соединения.
     * @param dbname Имя дб.
     * @param path Путь базе данных.
     */
    void setDatabaseName(const QString& dbname, const QString& path = {});

    /**
     * @brief Состояние базы данных.
     * @return Текущее состояние подключения базы данных.
     */
    LocalDBStatus status() const;

    /**
     * @brief Получить все элементы таблицы БД.
     * @param members Список членов структуры с ассоциируемой колонкой.
     * @return Массив основных элементов.
     */
    template<typename T, typename... Ts>
    QVector<T> getAllElements(const std::pair<const char*, Ts T::*>&... members) const;

    /**
     * @brief Добавить новую запись в БД.
     * @param values Варианты значений колонок.
     * @return Статус выполненной команды.
     */
    QSqlError addElement(const QVariantMap& values);

    /**
     * @brief Удалить запись в БД.
     * @param id в БД.
     * @return Статус выполненной команды.
     */
    QSqlError removeElement(quint64 id) const;

    /**
     * @brief Изменить запись в БД.
     * @param id в БД.
     * @param values Варианты значений колонок.
     * @return Статус выполненной команды.
     */
    QSqlError modifyElement(quint64 id, const QVariantMap& values) const;

private:
    LocalDBStatus createNewTable();
    LocalDBStatus readDataFromTable();

signals:
    void dbConnectionChanged(DatabaseCommon::LocalDBStatus newStatus);

protected:
    /**
     * @brief Установить параметры подключения БД.
     * @param table Название таблицы.
     * @param columns Названия колонок с опциональными значениями по умолчанию.
     * @param connectionName Название соединения.
     */
    void setContext(const QString& table,
                    const QVector<LocalDBColumn>& columns,
                    const QString &dbFilename,
                    const QString &dbFilepath,
                    const QString& connectionName = {});

    void updateDatabases();

private:
    template<typename T, typename... Ts>
    QVector<T> getAllDBElements(const QSqlDatabase& db, const std::pair<const char*, Ts T::*>&... members) const;

    QSqlDatabase _db;

    QString _name{};

    QString _table{};
    QVector<LocalDBColumn> _columns{};
    QString _connection{};
    LocalDBStatus _status = LocalDBStatus::Unknown;
};



// impl
// begin Detail
namespace Detail {

// closing recursion
template<typename T>
void getMembers(T&, QSqlQuery&, const int*)
{
}

// main recursive case, I is the column index
template<typename T, typename MemberT, typename... MemberTs>
void getMembers(T& val, QSqlQuery& query, const int* indIt, MemberT T::* member, MemberTs T::*... rest)
{
    // chip away MemberT at position I, forward the rest with an incremented column count
    val.*member = query.value(*indIt).value<MemberT>();
    getMembers(val, query, indIt + 1, rest...);
}

}
// end Detail

template<typename T, typename... Ts>
QVector<T> LocalDBProviderBase::getAllElements(const std::pair<const char*, Ts T::*>&... members) const
{
    return getAllDBElements(_db, members...);
}

template<typename T, typename... Ts>
QVector<T> LocalDBProviderBase::getAllDBElements(const QSqlDatabase& db,
                                                 const std::pair<const char*, Ts T::*>&... members) const
{
    QVector<T> retData;
    if (_status != LocalDBStatus::Connected)
        return retData;

    auto query = db.exec("SELECT * FROM " + _table);
    if (query.size() > 0)
        retData.reserve(query.size());

    const auto record = query.record();
    const std::array<int, sizeof...(Ts)> indArr{record.indexOf(members.first)...};

    while (query.next())
    {
        T data;
        auto vaue = query.value(1);
        Detail::getMembers(data, query, indArr.data(), members.second...);
        retData.push_back(std::move(data));
    }
    return retData;
}

}

#endif // LOCALDBPROVIDERBASE_H
