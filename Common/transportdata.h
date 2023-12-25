#ifndef TRANSPORTDATA_H
#define TRANSPORTDATA_H

#include <QString>
#include <QVariantMap>
#include <QDateTime>

/**
 * @brief Структура транспортного средства из базы данных.
 * @details Именна соответствуют полям в БД.
 */
struct TransportData
{
    int id;                 ///< Идентификатор записи
    QString model;          ///< Модель
    int year;               ///< Год выпуска
    int count;              ///< Количество
    QString condition;      ///< Состояние транспорта
    bool inStock;           ///< Сейчас в наличии
    quint64 receiptDate;    ///< Дата поступления
    QString manufacturer;   ///< Поставщик

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"model", model},
            {"year", year},
            {"count", count},
            {"condition", condition},
            {"inStock", inStock},
            {"receiptDate", receiptDate},
            {"manufacturer", manufacturer},
        };
    }

    static TransportData fromDBMap(const QVariantMap &variant)
    {
        TransportData temp;
        temp.id = variant.value("id").toInt();
        temp.model = variant.value("model").toString();
        temp.year = variant.value("year").toInt();
        temp.count = variant.value("count").toInt();
        temp.condition = variant.value("condition").toString();
        temp.inStock = variant.value("inStock").toBool();
        temp.receiptDate = variant.value("receiptDate").toLongLong();
        temp.manufacturer = variant.value("manufacturer").toString();
        return temp;
    }

    QVariantMap toWidgetMap() const
    {
        return QVariantMap {
            {"Manufacturer", manufacturer},
            {"ID", id},
            {"Model", model},
            {"Year", year},
            {"Count", count},
            {"Condition", condition},
            {"Availability", inStock ? "In stock" : "Ordered"},
            {"Receipt date", QDateTime::fromMSecsSinceEpoch(receiptDate).toString("dd.MM.yyyy")},
        };
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"Model", "Year", "Count", "Condition", "Availability", "Receipt date", "Manufacturer"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "model", "year", "count", "condition", "inStock", "receiptDate", "manufacturer"};
    }

    inline bool operator == (const TransportData & other)
    {
        return model == other.model &&
               condition == other.condition &&
               year == other.year &&
               manufacturer == other.manufacturer &&
               QDateTime::fromMSecsSinceEpoch(receiptDate).date() == QDateTime::fromMSecsSinceEpoch(other.receiptDate).date();
    }

    inline bool operator != (const TransportData & other)
    {
        return !this->operator==(other);
    }
};

#endif // TRANSPORTDATA_H
