#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariantMap>
#include <QDateTime>

/**
 * @brief Структура машины из базы данных.
 * @details Именна соответствуют полям в БД.
 */
struct PurchaseData
{
    int id;             ///< Идентификатор записи
    int userId;         ///< Идентификатор пользователя
    int transportId;    ///< Идентификатор транспортного средства
    int manufacturerId; ///< Идентификатор производителя
    int count;          ///< Количество купленного товара
    quint64 date;       ///< Дата и время покупки
    quint64 price;      ///< Сумма покупки

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"userId", userId},
            {"transportId", transportId},
            {"manufacturerId", manufacturerId},
            {"count", count},
            {"date", date},
            {"price", price},
        };
    }

    static PurchaseData fromDBMap(const QVariantMap &variant)
    {
        PurchaseData temp;
        temp.id = variant.value("id").toInt();
        temp.userId = variant.value("userId").toInt();
        temp.transportId = variant.value("transportId").toInt();
        temp.manufacturerId = variant.value("manufacturerId").toInt();
        temp.count = variant.value("count").toInt();
        temp.date = variant.value("date").toLongLong();
        temp.price = variant.value("price").toLongLong();
        return temp;
    }

    static QStringList wigdetKeys()
    {
        return QStringList {"User ID", "Transport ID", "Manufacturer ID", "Count", "Date", "Price"};
    }

    static QStringList DBKeys()
    {
        return QStringList {"id", "userId", "transportId", "manufacturerId", "count", "date", "price"};
    }
};

#endif // PURCHASEDATA_H
