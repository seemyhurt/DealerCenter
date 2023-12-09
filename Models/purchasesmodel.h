#ifndef PURCHASESMODEL_H
#define PURCHASESMODEL_H


#include <QStandardItemModel>

class PurchasesDBService;
class TransportDBService;
class UserDBService;
class ManufacturerDBService;
struct PurchaseData;
struct TransportData;

class PurchasesModel : public QStandardItemModel
{
    Q_OBJECT
public:
    PurchasesModel(QObject * parent = nullptr);
    void setCurrentUser(quint64 number);;

private slots:
    void handleNeedUpdatePurchase(const PurchaseData& data);
    void handleNeedModifyPurchase(const TransportData &data);

private:
    void generatePurchaseItem(const PurchaseData& data);
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QSharedPointer<PurchasesDBService> _purchaseService;
    QSharedPointer<TransportDBService> _transportService;
    QSharedPointer<UserDBService> _userService;
    QSharedPointer<ManufacturerDBService> _manufacturerService;
    quint64 _currentUserNumber;
};

#endif // PURCHASESMODEL_H
