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
                       QVariantMap& values,
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
     * @brief Вернуть максимальное значение ID в БД
     */
    int maxId() const;

    /**
     * @brief Вернуть ID последнего добавленного элемента БД
     */
    int lastInsertId() const;

    /**
     * @brief Таблица основных элементов.
     * @return Ссылка на таблицу.
     */
    const QHash<quint64, T>& elements() const { return _elements; }

private:
    QHash<quint64, T> _elements;
    int _maxId = 0;
    int _lastInsertId = 0;
};


// impl
template<typename T>
void LocalDBStorage<T>::constructElements(QVector<T>&& main)
{
    clear();
    for (auto& el : main)
    {
        _elements.insert(el.id, std::move(el));
        _maxId = std::max(_maxId, el.id);
    }
}

template<typename T>
QSqlError LocalDBStorage<T>::removeEntry(LocalDBProviderBase* provider, quint64 id)
{
    auto ret = provider->removeElement(id);
    if (ret.type() != QSqlError::ErrorType::NoError)
        return ret;

    _elements.remove(id);

    if (_maxId == id)
    {
        int maxId = 0;
        for (const auto &el : qAsConst(_elements))
            maxId = std::max(maxId, el.id);
        _maxId = maxId;
    }
    if (_lastInsertId == id)
        _lastInsertId = 0;

    return ret;
}

template<typename T>
QSqlError LocalDBStorage<T>::addEntry(LocalDBProviderBase* provider,
                                      QVariantMap& valuesMap,
                                      const T & value)
{
    auto id = valuesMap["id"].toInt();

    QSqlError ret;
    if (_elements.contains(id))
        ret = provider->modifyElement(id, valuesMap);
    else
        ret = provider->addElement(valuesMap);

    if (ret.type() != QSqlError::ErrorType::NoError)
        return ret;

    _elements[id] = value;
    _maxId = std::max(_maxId, id);
    _lastInsertId = id;

    return ret;
}

template<typename T>
void LocalDBStorage<T>::clear()
{
    _elements.clear();
    _maxId = 0;
    _lastInsertId = 0;
}

template<typename T>
quint64 LocalDBStorage<T>::size() const
{
    return _elements.size();
}

template<typename T>
int LocalDBStorage<T>::maxId() const
{
    return _maxId;
}

template<typename T>
int LocalDBStorage<T>::lastInsertId() const
{
    return _lastInsertId;
}

}
#endif // LOCALBBSTORAGE_H
