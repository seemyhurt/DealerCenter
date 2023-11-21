#ifndef MANUFACTURERDBPROVIDER_H
#define MANUFACTURERDBPROVIDER_H

#include "localdbproviderbase.h"

struct ManufacturerData;
/**
 * @brief Провайдер БД машин.
 */
class ManufacturerDBProvider
    : public DatabaseCommon::LocalDBProviderBase
{
    Q_OBJECT

public:
    /**
     * @brief Default конструктор.
     * @param parent Родитель.
     */
    explicit ManufacturerDBProvider(QObject* parent = nullptr);

    /**
     * @brief Метод доступа к машинам БД.
     * @return Массив машин.
     */
    QVector<ManufacturerData> getManufacturers();

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();
};

#endif // MANUFACTURERDBPROVIDER_H
