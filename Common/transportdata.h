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
    quint64 receiptDate = 0;///< Дата поступления
    QString manufacturer;   ///< Поставщик

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"model", model},
            {"year", year},
            {"count", count},
            {"condition", condition},
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
            {"Receipt date", receiptDate == 0 ? "Unavailable" : QDateTime::fromMSecsSinceEpoch(receiptDate).toString("dd.MM.yyyy")},
        };
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"Model", "Year", "Count", "Condition", "Receipt date", "Manufacturer"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "model", "year", "count", "condition", "receiptDate", "manufacturer"};
    }

    inline bool operator == (const TransportData & other)
    {
        bool res =  model == other.model &&
               condition == other.condition &&
               year == other.year &&
               manufacturer == other.manufacturer;

        if (receiptDate == 0 || other.receiptDate == 0) return res;

        return res && QDateTime::fromMSecsSinceEpoch(receiptDate).date() == QDateTime::fromMSecsSinceEpoch(other.receiptDate).date();
    }

    inline bool operator != (const TransportData & other)
    {
        return !this->operator==(other);
    }

    inline bool isValid()
    {
        static const int MaxStringSize = 30;
        if (model.isEmpty() ||
            condition.isEmpty() ||
            manufacturer.isEmpty())
        {
            return false;
        }

        if (model.size() > MaxStringSize ||
            condition.size() > MaxStringSize ||
            manufacturer.size() > MaxStringSize)
        {
            return false;
        }

        if (year <= 1997 ||
            year > QDate::currentDate().year())
        {
            return false;
        }

        if (receiptDate < 0)
        {
            return false;
        }

        if (count < 0 ||
            count > 999999999)
        {
            return false;
        }
        return true;
    }
};

#endif // TRANSPORTDATA_H
