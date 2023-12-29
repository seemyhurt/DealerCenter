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
    _tabs(new QTabWidget(this)),
    _customersWidget(new CustomersTableWidget(this)),
    _manufacturersWidget(new ManufacturersTableWidget(manufacturerModel, true, this)),
    _managersWidget(new ManagersTableWidget(this)),
    _transportsWidget(new TransportTableWidget(transportModel, this))
{
    _tabs->addTab(_customersWidget, "Customers");
    _tabs->addTab(_manufacturersWidget, "Manufacturers");
    _tabs->addTab(_managersWidget, "Managers");
    _tabs->addTab(_transportsWidget, "Transport");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs);
    setLayout(_tabs->layout());
}
