#include "purchasestablewidget.h"
#include "../Models/purchasesmodel.h"

#include <QTreeView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QMessageBox>

PurchasesTableWidget::PurchasesTableWidget(QSharedPointer<PurchasesModel> model,
                                           QWidget *parent)
    : QWidget(parent),
    _purchasesModel(model)
{
    auto tableView = new QTreeView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setHeaderHidden(true);

    auto layout = new QVBoxLayout(this);
    tableView->setModel(_purchasesModel.data());
    layout->addWidget(tableView);

    setLayout(layout);
}

void PurchasesTableWidget::setCurrentUser(quint64 number)
{
    if (_purchasesModel)
        _purchasesModel->setCurrentUser(number);
}
