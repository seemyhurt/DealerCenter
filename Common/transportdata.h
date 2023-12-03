#ifndef TRANSPORTDATA_H
#define TRANSPORTDATA_H

#include <QString>
#include <QVariantMap>
#include  <QDateTime>

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
    QString condition;      ///< Состояние транспорта
    QString type;           ///< Тип транспортного средства
    bool inStock;           ///< Сейчас в наличии
    quint64 receiptDate;    ///< Дата поступления
    int guaranteePeriod;    ///< Период гарантии

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"brand", brand},
            {"model", model},
            {"price", price},
            {"year", year},
            {"count", count},
            {"condition", condition},
            {"type", type},
            {"inStock", inStock},
            {"receiptDate", receiptDate},
            {"guaranteePeriod", guaranteePeriod}
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
        temp.condition = variant.value("condition").toString();
        temp.type = variant.value("type").toString();
        temp.inStock = variant.value("inStock").toBool();
        temp.receiptDate = variant.value("receiptDate").toLongLong();
        temp.guaranteePeriod = variant.value("guaranteePeriod").toInt();
        return temp;
    }

    QVariantMap toWidgetMap() const
    {
        return QVariantMap {
            {"ID", id},
            {"Brand", brand},
            {"Model", model},
            {"Price", price},
            {"Year", year},
            {"Count", count},
            {"Condition", condition},
            {"Type", type},
            {"In stock", inStock ? "In stock" : "Ordered"},
            {"Receipt date", QDateTime::fromMSecsSinceEpoch(receiptDate).toString("dd.MM.yyyy HH:mm")},
            {"Guarantee period", guaranteePeriod}
        };
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"ID", "Brand", "Model", "Price", "Year", "Count", "Condition", "Type", "In stock", "Receipt date", "Guarantee period"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "brand", "model", "price", "year", "count", "condition", "type", "inStock", "receiptDate", "guaranteePeriod"};
    }
};

#endif // TRANSPORTDATA_H
