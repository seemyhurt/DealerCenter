#ifndef MANUFACTURERDBSERVICE_H
#define MANUFACTURERDBSERVICE_H

#include "ilocaldbservicebase.h"
#include "../Providers/localbbstorage.h"
#include <QSharedPointer>

struct ManufacturerData;
class ManufacturerDBProvider;

class ManufacturerDBService : public DatabaseCommon::ILocalDBServiceBase
{
    Q_OBJECT
public:
    explicit ManufacturerDBService(QObject *parent = nullptr);

    // ILocalDBServiceBase interface
    quint64 tableSize() const override;
    QSqlError addEntry(QVariantMap &values) override;
    QSqlError removeEntry(quint64 id) override;

    /**
     * @brief Возвращает уникальный ключ сервиса
     * @return Строка с ключом
     */
    static QString baseKey();

    QVariantList getAllManufacturers();
    QStringList getAvailableBrands();
    QStringList getManufacturersByBrand(const QString & brand);

signals:
    void manufacturerAdded(const ManufacturerData & data);

protected slots:
    /**
     * @brief Реализация изменения статуса БД.
     * @param status Новое состояние БД.
     */
    void handleDbConnectionChange(DatabaseCommon::LocalDBStatus status);

private:
    void selectDataFromStorage();

private:
    DatabaseCommon::LocalDBStorage<ManufacturerData> _storage;
    QSharedPointer<ManufacturerDBProvider> _provider;
    QHash<QString, QVector<ManufacturerData>> _manufacturersToBrand;
};

#endif // MANUFACTURERDBSERVICE_H
