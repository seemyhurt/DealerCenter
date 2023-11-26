#include "purchasewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/manufacturerdbservice.h"
#include "../Common/manufacturerdata.h"

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

PurchaseWidget::PurchaseWidget(QWidget *parent) :
    QWidget(parent),
    _service(ServiceLocator::service<ManufacturerDBService>())
{
    auto lblBrand = new QLabel("&Brand", this);
    brand = new QComboBox(this);
    lblBrand->setBuddy(brand);

    auto lblManufacturers = new QLabel("&Manufacturer", this);
    manufacturer = new QComboBox(this);
    lblManufacturers->setBuddy(lblManufacturers);

    auto lblCondition = new QLabel("&Condition", this);
    condition = new QComboBox(this);
    lblCondition->setBuddy(condition);
    condition->addItems({"New", "Old model", "Previously used"});

    auto lblModel = new QLabel("&Model", this);
    auto model = new QLineEdit(this);
    lblModel->setBuddy(model);

    auto lblYear = new QLabel("&Year", this);
    year = new QLineEdit(this);
    lblYear->setBuddy(year);

    brand->addItems(_service->getAvailableBrands());

    connect(brand, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleBrandChanged);
    connect(condition, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleConditionChanged);
    connect(_service.data(), &ManufacturerDBService::manufacturerAdded, this, &PurchaseWidget::handleManufacturerAdded);

    auto buttonBuy = new QPushButton("Buy new car", this);

    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(brand, 0, 1);
    layout->addWidget(lblBrand, 0, 0);
    layout->addWidget(manufacturer, 1, 1);
    layout->addWidget(lblManufacturers, 1, 0);
    layout->addWidget(condition, 2, 1);
    layout->addWidget(lblCondition, 2, 0);
    layout->addWidget(model, 3, 1);
    layout->addWidget(lblModel, 3, 0);
    layout->addWidget(year, 4, 1);
    layout->addWidget(lblYear, 4, 0);
    layout->addWidget(buttonBuy, 5, 1);

    setLayout(layout);
    handleBrandChanged(brand->currentText());
    handleConditionChanged(condition->currentText());
}

void PurchaseWidget::handleBrandChanged(const QString &brand)
{
    manufacturer->clear();
    manufacturer->addItems(_service->getManufacturersByBrand(brand));
}

void PurchaseWidget::handleConditionChanged(const QString &condition)
{
    if (condition == QLatin1String("New"))
    {
        year->setText("2023");
        year->setReadOnly(true);
    }
    else
    {
        year->clear();
        year->setReadOnly(false);
    }
}

void PurchaseWidget::handleManufacturerAdded(const ManufacturerData & data)
{
    auto index = brand->findText(data.carBrand);
    if (index == -1)
        brand->addItem(data.carBrand);
    else if (index == brand->currentIndex())
        manufacturer->addItem(data.name);
}
