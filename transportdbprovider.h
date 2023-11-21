#ifndef TransportDBProvider_H
#define TransportDBProvider_H

#include "localdbproviderbase.h"

struct TransportData;
/**
 * @brief Провайдер БД машин.
 */
class TransportDBProvider
    : public DatabaseCommon::LocalDBProviderBase
{
    Q_OBJECT

public:
    /**
     * @brief Default конструктор.
     * @param parent Родитель.
     */
    explicit TransportDBProvider(QObject* parent = nullptr);

    /**
     * @brief Метод доступа к машинам БД.
     * @return Массив машин.
     */
    QVector<TransportData> getCars();

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();
};

#endif // TransportDBProvider_H
