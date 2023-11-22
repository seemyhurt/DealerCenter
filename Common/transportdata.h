#ifndef TRANSPORTDATA_H
#define TRANSPORTDATA_H

#include <QString>
#include <QVariantMap>

/**
 * @brief Структура машины из базы данных.
 * @details Именна соответствуют полям в БД.
 */
struct TransportData
{
    int id;                 ///< Идентификатор записи
    QString brand;          ///< Марка
    QString model;          ///< Модель
    int price;              ///< Цена
    int year;               ///< Год выпуска
    int count;              ///< Количество

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"brand", brand},
            {"model", model},
            {"price", price},
            {"year", year},
            {"count", count}
        };
    }

    static TransportData fromDBMap(const QVariantMap &variant)
    {
        TransportData temp;
        temp.id = variant.value("id").toInt();
        temp.brand = variant.value("brand").toString();
        temp.model = variant.value("model").toString();
        temp.price = variant.value("price").toInt();
        temp.year = variant.value("year").toInt();
        temp.count = variant.value("count").toInt();
        return temp;
    }

    QVariantMap toWidgetMap() const
    {
        return QVariantMap {
            {"id", id},
            {"Brand", brand},
            {"Model", model},
            {"Price", price},
            {"Year", year},
            {"Count", count}
        };
    }
};

#endif // TRANSPORTDATA_H
