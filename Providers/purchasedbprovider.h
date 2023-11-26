#ifndef PURCHASEDBPROVIDER_H
#define PURCHASEDBPROVIDER_H

#include "localdbproviderbase.h"

struct PurchaseData;
/**
 * @brief Провайдер БД покупок.
 */
class PurchaseDBProvider
    : public DatabaseCommon::LocalDBProviderBase
{
    Q_OBJECT

public:
    /**
     * @brief Default конструктор.
     * @param parent Родитель.
     */
    explicit PurchaseDBProvider(QObject* parent = nullptr);

    /**
     * @brief Метод доступа к покупкам из БД.
     * @return Массив пользователей.
     */
    QVector<PurchaseData> getPurchases();

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();
};

#endif // PURCHASEDBPROVIDER_H
