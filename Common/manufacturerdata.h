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
    quint64 basePrice;      ///< закупочная цена транспортного средства

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"name", name},
            {"deliveryTime", deliveryTime},
            {"guaranteePeriod", guaranteePeriod},
            {"transportBrand", transportBrand},
            {"type", type},
            {"basePrice", basePrice},
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
        temp.basePrice = variant.value("basePrice").toLongLong();
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
            {"Transport type", type},
            {"Base price", basePrice}
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
        temp.basePrice = variant.value("Base price").toLongLong();
        return temp;
    }

    QVariantMap toTransportInfoMap() const
    {
        return QVariantMap {
            {"Guarantee, years", guaranteePeriod},
            {"Brand", transportBrand},
            {"Type", type}
        };
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"Name", "Delivery time, days", "Guarantee period, years", "Transport brand", "Transport type", "Base price"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "name", "deliveryTime", "guaranteePeriod", "transportBrand", "type", "basePrice"};
    }

    static QStringList CustomerKeys()
    {
        return QStringList {"Type", "Brand", "Guarantee, years" };
    }

    inline bool isValid()
    {
        static const int MaxStringSize = 30;
        if (name.isEmpty() ||
            transportBrand.isEmpty() ||
            type.isEmpty())
        {
            return false;
        }

        if (!name.at(0).isUpper() ||
            !transportBrand.at(0).isUpper() ||
            !type.at(0).isUpper())
        {
            return false;
        }

        if (name.size() > MaxStringSize ||
            transportBrand.size() > MaxStringSize ||
            transportBrand.size() > MaxStringSize)
        {
            return false;
        }

        if (deliveryTime <= 0 ||
            deliveryTime > 100)
        {
            return false;
        }

        if (guaranteePeriod <= 0 ||
            guaranteePeriod > 10)
        {
            return false;
        }

        if (basePrice <= 0 ||
            basePrice > 999999999)
        {
            return false;
        }
        return true;
    }
};

#endif // MANUFACTURERDATA_H
