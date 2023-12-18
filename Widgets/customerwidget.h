#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class TransportTableWidget;
class PurchaseWidget;
class PurchasesTableWidget;
struct UserData;
class PurchasesModel;
class TransportsModel;

class CustomerWidget : public QWidget
{
    Q_OBJECT
public:
    CustomerWidget(QSharedPointer<TransportsModel> transportModel,
                   QSharedPointer<PurchasesModel> purchaseModel,
                   QWidget * parent = nullptr);

    bool loginCutomer();

signals:
    void newUserRegistred();

private slots:
    void handleRegisterUser();

private:
    QSharedPointer<UserDBService> _service;
    QSharedPointer<TransportTableWidget> _transportsWidget;
    QSharedPointer<PurchaseWidget> _purchasesWidget;
    QSharedPointer<PurchasesTableWidget> _purchasesTableWidget;
};

#endif // CUSTOMERWIDGET_H
