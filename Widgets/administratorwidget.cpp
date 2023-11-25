#include "administratorwidget.h"
#include "customerstablewidget.h"
#include "manufacturerstablewidget.h"
#include "managerstablewidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>

AdministratorWidget::AdministratorWidget(QWidget *parent)
    : QWidget(parent),
    _tabs(QSharedPointer<QTabWidget>::create(this)),
    _customersWidget(QSharedPointer<CustomersTableWidget>::create(this)),
    _manufacturersWidget(QSharedPointer<ManufacturersTableWidget>::create(this)),
    _managersWidget(QSharedPointer<ManagersTableWidget>::create(this))
{
    QStringList lst;
    lst << "Transport";
    for (const auto &str : qAsConst(lst))
        _tabs->addTab(new QLabel(str, _tabs.data()), str);

    _tabs->addTab(_customersWidget.data(), "Customers");
    _tabs->addTab(_manufacturersWidget.data(), "Manufacturers");
    _tabs->addTab(_managersWidget.data(), "Managers");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_tabs.data());
    setLayout(_tabs->layout());
}
