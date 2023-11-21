#ifndef LOCALBBSTORAGE_H
#define LOCALBBSTORAGE_H

#include <QHash>
#include "localdbproviderbase.h"

namespace DatabaseCommon {

/**
 * @brief Структура элементов БД.
 * @tparam T тип элемента БД.
 */

template<typename T>
class LocalDBStorage
{
public:
    /**
     * @brief Сконструировать основные и дочерние таблицы элементов.
     * @param main Массив элементов основной БД.
     */
    void constructElements(QVector<T>&& main);

    /**
     * @brief Удалить элемент из БД.
     * @param provider Указатель на провайдера БД.
     * @param id ID удаляемого элемента.
     * @return Статус ошибки выполненной команды.
     */
    QSqlError removeEntry(LocalDBProviderBase* provider, quint64 id);

    /**
     * @brief Добавить или обновить элемент в БД.
     * @details Пример аргументов в `members`:
     * @param provider Указатель на провайдера БД.
     * @param values Варианты значений колонок.
     * @param id ID элемента для модификации, 0 создает новый элемент.
     * @return Статус ошибки выполненной команды.
     */
    QSqlError addEntry(LocalDBProviderBase* provider,
                       QVariantMap& values, bool needUpdate,
                       const T &value);

    /**
     * @brief Сбросить все элементы.
     */
    void clear();

    /**
     * @brief Общий размер таблиц основных элементов и элементов без родителя.
     * @return Общее количество элементов.
     */
    quint64 size() const;

    /**
     * @brief Таблица основных элементов.
     * @return Ссылка на таблицу.
     */
    const QHash<quint64, T>& elements() const { return _elements; }

private:
    QHash<quint64, T> _elements;
};



// impl
template<typename T>
void LocalDBStorage<T>::constructElements(QVector<T>&& main)
{
    clear();
    for (auto& el : main)
        _elements.insert(el.id, std::move(el));
}

template<typename T>
QSqlError LocalDBStorage<T>::removeEntry(LocalDBProviderBase* provider, quint64 id)
{
    auto ret = provider->removeElement(id);
    if (ret.type() != QSqlError::ErrorType::NoError)
        return ret;

    _elements.remove(id);
    return ret;
}

template<typename T>
QSqlError LocalDBStorage<T>::addEntry(LocalDBProviderBase* provider,
                                      QVariantMap& values, bool needUpdate,
                                      const T & value)
{
    auto id = values["id"].toInt();
    _elements[id] = value;

    if (!needUpdate)
        return provider->addElement(values);
    else
        return provider->modifyElement(id, values);
}

template<typename T>
void LocalDBStorage<T>::clear()
{
    _elements.clear();
}

template<typename T>
quint64 LocalDBStorage<T>::size() const
{
    return _elements.size();
}

}
#endif // LOCALBBSTORAGE_H
