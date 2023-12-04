#include "purchasestablewidget.h"
#include "../Models/purchasesmodel.h"

#include <QTreeView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QMessageBox>

PurchasesTableWidget::PurchasesTableWidget(QWidget *parent)
    : QWidget(parent),
    _purchasesModel(QSharedPointer<PurchasesModel>::create())
{
    auto tableView = new QTreeView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setHeaderHidden(true);

    auto layout = new QVBoxLayout(this);
    tableView->setModel(_purchasesModel.data());
    layout->addWidget(tableView);

    setLayout(layout);
}
