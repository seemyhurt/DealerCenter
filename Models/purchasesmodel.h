#ifndef PURCHASESMODEL_H
#define PURCHASESMODEL_H


#include <QStandardItemModel>

class PurchasesDBService;
class TransportDBService;
class UserDBService;
class ManufacturerDBService;
struct PurchaseData;

class PurchasesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    PurchasesModel(QObject * parent = nullptr);

private slots:
    void handleNeedUpdatePurchase(const PurchaseData& data);

private:
    QSharedPointer<PurchasesDBService> _purchaseService;
    QSharedPointer<TransportDBService> _transportService;
    QSharedPointer<UserDBService> _userService;
    QSharedPointer<ManufacturerDBService> _manufacturerService;
};

#endif // PURCHASESMODEL_H
