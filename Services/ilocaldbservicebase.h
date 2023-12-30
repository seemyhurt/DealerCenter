#ifndef ILOCALDBSERVICEBASE_H
#define ILOCALDBSERVICEBASE_H

#include "iservice.h"
#include <QSqlError>

class ILocalDBServiceBase : public IService
{
    Q_OBJECT
public:
    explicit ILocalDBServiceBase(QObject *parent = nullptr);

    /**
     * @brief Реализация размера таблицы.
     * @return Размер таблицы, включая новые пользовательские записи.
     */
    virtual quint64 tableSize() const = 0;

    /**
     * @brief Реализация функции добавления или обновления записи в БД.
     * @param values Новые значения колонок.
     * @return Результат ошибки провайдера.
     */
    virtual QSqlError addEntry(QVariantMap& values) = 0;

    /**
     * @brief Реализация функции удаления записи в БД.
     * @param ID записи.
     * @return Результат ошибки провайдера.
     */
    virtual QSqlError removeEntry(quint64 id) = 0;
};

#endif // ILOCALDBSERVICEBASE_H
