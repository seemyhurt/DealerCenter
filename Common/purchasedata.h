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
    int count;          ///< Количество купленного товара
    quint64 date;     ///< Дата и время покупки

    QVariantMap toDBMap() const
    {
        return QVariantMap {
            {"id", id},
            {"userId", userId},
            {"transportId", transportId},
            {"count", count},
            {"date", date},
        };
    }

    static PurchaseData fromDBMap(const QVariantMap &variant)
    {
        PurchaseData temp;
        temp.id = variant.value("id").toInt();
        temp.userId = variant.value("userId").toInt();
        temp.transportId = variant.value("transportId").toInt();
        temp.count = variant.value("count").toInt();
        temp.date = variant.value("date").toLongLong();
        return temp;
    }
};

#endif // PURCHASEDATA_H
