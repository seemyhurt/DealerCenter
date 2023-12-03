#include "manufacturerstablewidget.h"
#include "inputmanufacturerdialog.h"

#include "../Models/manufacturersmodel.h"
#include "../Common/manufacturerdata.h"

#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QMessageBox>

ManufacturersTableWidget::ManufacturersTableWidget(bool enableControl, QWidget *parent)
    : QWidget(parent),
    _manufacturersModel(QSharedPointer<ManufacturersModel>::create())
{
    auto tableView = new QTableView(this);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView->verticalHeader()->setVisible(false);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);

    auto layout = new QVBoxLayout(this);

    tableView->setModel(_manufacturersModel.data());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(tableView);

    if (enableControl)
    {
        auto buttonAdd = new QPushButton("Add new manufacturer", this);
        connect(buttonAdd, &QPushButton::clicked, this, &ManufacturersTableWidget::handleNeedAddManufacturer);
        layout->addWidget(buttonAdd);
    }

    setLayout(layout);
}

void ManufacturersTableWidget::handleNeedAddManufacturer()
{
    auto dialog = new InputManufacturerDialog();
    if (dialog->exec() != QDialog::Accepted)
        return;

    auto manufacturer = dialog->getDialogInfo();

    if (_manufacturersModel->addNewManufacturer(manufacturer))
        QMessageBox::information(this, "Successfully added", "Manufacturer successfully added!");
    else
        QMessageBox::warning(nullptr, "Error", "Incorrect manufacturer data");
}
