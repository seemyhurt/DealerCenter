#include "purchasewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/manufacturerdbservice.h"

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

PurchaseWidget::PurchaseWidget(QWidget *parent) :
    QWidget(parent),
    _service(ServiceLocator::service<ManufacturerDBService>())
{
    auto lblBrand = new QLabel("Brand", this);
    auto brand = new QComboBox(this);
    lblBrand->setBuddy(brand);

    auto lblManufacturers = new QLabel("Nanufacturer", this);
    manufacturer = new QComboBox(this);
    lblManufacturers->setBuddy(lblManufacturers);

    auto lblModel = new QLabel("Model", this);
    auto model = new QLineEdit(this);
    lblModel->setBuddy(model);

    brand->addItems(_service->getAvailableBrands());

    connect(brand, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleBrandChanged);

    auto buttonBuy = new QPushButton("Buy new car", this);

    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(brand, 0, 1);
    layout->addWidget(lblBrand, 0, 0);
    layout->addWidget(manufacturer, 1, 1);
    layout->addWidget(lblManufacturers, 1, 0);
    layout->addWidget(model, 2, 1);
    layout->addWidget(lblModel, 2, 0);
    layout->addWidget(buttonBuy, 3, 1);

    setLayout(layout);
    handleBrandChanged(brand->currentText());
}

void PurchaseWidget::handleBrandChanged(const QString &brand)
{
    manufacturer->clear();
    manufacturer->addItems(_service->getManufacturersByBrand(brand));
}
