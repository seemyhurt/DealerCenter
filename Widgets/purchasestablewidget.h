#ifndef PURCHASESTABLEWIDGET_H
#define PURCHASESTABLEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class PurchasesModel;
class PurchasesDBService;
struct PurchasesData;

class PurchasesTableWidget : public QWidget
{
    Q_OBJECT
public:
    PurchasesTableWidget(QSharedPointer<PurchasesModel> model,
                         QWidget * parent = nullptr);
    void setCurrentUser(quint64 number);;

private:
    QSharedPointer<PurchasesModel> _purchasesModel;
};

#endif // PURCHASESTABLEWIDGET_H
