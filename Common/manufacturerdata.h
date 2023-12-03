#ifndef MANUFACTURERDATA_H
#define MANUFACTURERDATA_H

#include <QVariantMap>

/**
 * @brief Структура производителя из базы данных.
 * @details Именна соответствуют полям в БД.
 */

struct ManufacturerData
{
    int id;                 ///< идентификатор записи
    QString name;           ///< название производителя
    int deliveryTime;       ///< сроки поставки
    int guaranteePeriod;    ///< срок гарантии на поставляемые товары
    QString transportBrand; ///< брэнд выпускаемых транспортных средств
    QString type;           ///< тип выпускаемых транспортных средств 


    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"name", name},
            {"deliveryTime", deliveryTime},
            {"guaranteePeriod", guaranteePeriod},
            {"transportBrand", transportBrand},
            {"type", type}
        };
    }

    static ManufacturerData fromDBMap(const QVariantMap &variant)
    {
        ManufacturerData temp;
        temp.id = variant.value("id").toInt();
        temp.name = variant.value("name").toString();
        temp.deliveryTime = variant.value("deliveryTime").toInt();
        temp.guaranteePeriod = variant.value("guaranteePeriod").toInt();
        temp.transportBrand = variant.value("transportBrand").toString();
        temp.type = variant.value("type").toString();
        return temp;
    }

    QVariantMap toWidgetMap() const
    {
        return QVariantMap {
            {"ID", id},
            {"Name", name},
            {"Delivery time, days", deliveryTime},
            {"Guarantee period, years", guaranteePeriod},
            {"Transport brand", transportBrand},
            {"Transport type", type}
        };
    }

    static ManufacturerData fromWidgetMap(const QVariantMap &variant)
    {
        ManufacturerData temp;
        temp.id = variant.value("ID", 0).toInt();
        temp.name = variant.value("Name").toString();
        temp.deliveryTime = variant.value("Delivery time, days").toInt();
        temp.guaranteePeriod = variant.value("Guarantee period, years").toInt();
        temp.transportBrand = variant.value("Transport brand").toString();
        temp.type = variant.value("Transport type").toString();
        return temp;
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"ID", "Name", "Delivery time, days", "Guarantee period, years", "Transport brand", "Transport type"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "name", "deliveryTime", "guaranteePeriod", "transportBrand", "type"};
    }
};




#endif // MANUFACTURERDATA_H
