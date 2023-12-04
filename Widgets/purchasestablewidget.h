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
    PurchasesTableWidget(QWidget * parent = nullptr);

private:
    QSharedPointer<PurchasesModel> _purchasesModel;
};

#endif // PURCHASESTABLEWIDGET_H
