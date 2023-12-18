#include "administratorwidget.h"
#include "customerstablewidget.h"
#include "manufacturerstablewidget.h"
#include "managerstablewidget.h"
#include "transporttablewidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>

AdministratorWidget::AdministratorWidget(QSharedPointer<TransportsModel> transportModel,
                                         QSharedPointer<ManufacturersModel> manufacturerModel,
                                         QWidget *parent)
    : QWidget(parent),
    _tabs(QSharedPointer<QTabWidget>::create(this)),
    _customersWidget(QSharedPointer<CustomersTableWidget>::create(this)),
    _manufacturersWidget(QSharedPointer<ManufacturersTableWidget>::create(manufacturerModel, true, this)),
    _managersWidget(QSharedPointer<ManagersTableWidget>::create(this)),
    _transportsWidget(QSharedPointer<TransportTableWidget>::create(transportModel, this))
{
    _tabs->addTab(_customersWidget.data(), "Customers");
    _tabs->addTab(_manufacturersWidget.data(), "Manufacturers");
    _tabs->addTab(_managersWidget.data(), "Managers");
    _tabs->addTab(_transportsWidget.data(), "Transport");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs.data());
    setLayout(_tabs->layout());
}
