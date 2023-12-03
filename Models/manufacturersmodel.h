#ifndef MANUFACTURERSMODEL_H
#define MANUFACTURERSMODEL_H

#include <QStandardItemModel>

class ManufacturerDBService;
struct ManufacturerData;

class ManufacturersModel : public QStandardItemModel
{
    Q_OBJECT
public:
    ManufacturersModel(QObject * parent = nullptr);

    bool addNewManufacturer(const ManufacturerData& data);

    QStringList getAvailableBrands();

private slots:
    void handleNeedUpdateManufacturers(const ManufacturerData& data);

private:
    QSharedPointer<ManufacturerDBService> _manufacturersService;
};

#endif // MANUFACTURERSMODEL_H
