#ifndef TRANSPORTSMODEL_H
#define TRANSPORTSMODEL_H

#include <QStandardItemModel>

class TransportDBService;
struct TransportData;

class TransportsModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TransportsModel(QObject * parent = nullptr);

private slots:
    void handleNeedUpdateTransports(const TransportData& data);

private:
    QSharedPointer<TransportDBService> _transportService;
};

#endif // TRANSPORTSMODEL_H
