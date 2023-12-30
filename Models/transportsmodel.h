#ifndef TRANSPORTSMODEL_H
#define TRANSPORTSMODEL_H

#include <QStandardItemModel>

class TransportDBService;
class ManufacturerDBService;
struct TransportData;

class TransportsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TransportsModel(QObject * parent = nullptr);

private:
    void addTransportToModel(const TransportData& data);

private slots:
    void handleNeedUpdateTransports(const TransportData& data);
    void handleNeedModifyTransports(const TransportData& data);

private:
    QSharedPointer<TransportDBService> _transportService;
    QSharedPointer<ManufacturerDBService> _manufacturerService;
};

#endif // TRANSPORTSMODEL_H
