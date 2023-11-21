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
    QString carBrand;       ///< брэнд выпускаемых автомобилей


    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"name", name},
            {"deliveryTime", deliveryTime},
            {"guaranteePeriod", guaranteePeriod},
            {"carBrand", carBrand}
        };
    }

    static ManufacturerData fromDBMap(const QVariantMap &variant)
    {
        ManufacturerData temp;
        temp.id = variant.value("id").toInt();
        temp.name = variant.value("name").toString();
        temp.deliveryTime = variant.value("deliveryTime").toInt();
        temp.guaranteePeriod = variant.value("guaranteePeriod").toInt();
        temp.carBrand = variant.value("carBrand").toString();
        return temp;
    }

    QVariantMap toWigdetMap() const
    {
        return QVariantMap {
            {"id", id},
            {"Name", name},
            {"Delivery time", deliveryTime},
            {"Guarantee period", guaranteePeriod},
            {"Car brand", carBrand}
        };
    }
};




#endif // MANUFACTURERDATA_H
