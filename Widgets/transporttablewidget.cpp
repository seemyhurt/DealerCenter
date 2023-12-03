#include "transporttablewidget.h"
#include "../Models/transportsmodel.h"

#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QStandardItemModel>

TransportTableWidget::TransportTableWidget(QWidget *parent)
    : QWidget(parent),
    _transportModel(QSharedPointer<TransportsModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->verticalHeader()->setVisible(false);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);

    auto layout = new QVBoxLayout(this);

    tableView->setModel(_transportModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(tableView);
    setLayout(layout);
}
