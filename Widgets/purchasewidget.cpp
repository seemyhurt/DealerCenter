#include "purchasewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/manufacturerdbservice.h"
#include "../Services/userdbservice.h"
#include "../Services/purchasesdbservice.h"
#include "../Services/transportdbservice.h"
#include "../Common/manufacturerdata.h"
#include "../Common/transportdata.h"
#include "../Common/purchasedata.h"

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDateTime>
#include <QSpinBox>

PurchaseWidget::PurchaseWidget(QWidget *parent) :
    QWidget(parent),
    _manufacturersService(ServiceLocator::service<ManufacturerDBService>()),
    _usersService(ServiceLocator::service<UserDBService>()),
    _transportService(ServiceLocator::service<TransportDBService>()),
    _purchasesService(ServiceLocator::service<PurchasesDBService>())
{
    auto lblType = new QLabel("&Transport type", this);
    _type = new QComboBox(this);
    lblType->setBuddy(_type);

    auto lblBrand = new QLabel("&Brand", this);
    _brand = new QComboBox(this);
    lblBrand->setBuddy(_brand);

    auto lblManufacturers = new QLabel("&Manufacturer", this);
    _manufacturer = new QComboBox(this);
    lblManufacturers->setBuddy(lblManufacturers);

    auto lblCondition = new QLabel("&Condition", this);
    _condition = new QComboBox(this);
    lblCondition->setBuddy(_condition);
    _condition->addItems({"New", "Old model", "Previously used"});

    auto lblModel = new QLabel("&Model", this);
    _model = new QLineEdit(this);
    lblModel->setBuddy(_model);

    auto lblYear = new QLabel("&Year", this);
    _year = new QLineEdit(this);
    lblYear->setBuddy(_year);

    auto lblCount = new QLabel("&Count", this);
    _count = new QSpinBox(this);
    lblCount->setBuddy(_count);
    _count->setMaximum(100);
    _count->setMinimum(1);

    _brand->addItems(_manufacturersService->getAvailableBrands());
    _type->addItems(_manufacturersService->getAvailableTypes());

    connect(_type, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleTypeChanged);
    connect(_brand, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleBrandChanged);
    connect(_condition, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleConditionChanged);
    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &PurchaseWidget::handleManufacturerAdded);

    auto buttonBuy = new QPushButton("Buy new car", this);
    connect(buttonBuy, &QPushButton::clicked, this, &PurchaseWidget::handleCreatePurchase);

    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(lblType, 0, 0);
    layout->addWidget(_type, 0, 1);
    layout->addWidget(lblBrand, 1, 0);
    layout->addWidget(_brand, 1, 1);
    layout->addWidget(lblManufacturers, 2, 0);
    layout->addWidget(_manufacturer, 2, 1);
    layout->addWidget(lblCondition, 3, 0);
    layout->addWidget(_condition, 3, 1);
    layout->addWidget(lblModel, 4, 0);
    layout->addWidget(_model, 4, 1);
    layout->addWidget(lblYear, 5, 0);
    layout->addWidget(_year, 5, 1);
    layout->addWidget(lblCount, 6, 0);
    layout->addWidget(_count, 6, 1);
    layout->addWidget(buttonBuy, 7, 1);

    setLayout(layout);
    handleTypeChanged(_type->currentText());
    handleBrandChanged(_brand->currentText());
    handleConditionChanged(_condition->currentText());
}

void PurchaseWidget::handleBrandChanged(const QString &brand)
{
    _manufacturer->clear();
    _manufacturer->addItems(_manufacturersService->getManufacturersByBrand(brand));
}

void PurchaseWidget::handleTypeChanged(const QString &type)
{
    _brand->clear();
    _brand->addItems(_manufacturersService->getManufacturersByType(type));
}

void PurchaseWidget::handleConditionChanged(const QString &condition)
{
    if (condition == QLatin1String("New"))
    {
        _year->setText("2023");
        _year->setReadOnly(true);
    }
    else
    {
        _year->clear();
        _year->setReadOnly(false);
    }
}

void PurchaseWidget::handleManufacturerAdded(const ManufacturerData & data)
{
    auto index = _brand->findText(data.transportBrand);
    if (index == -1)
        _brand->addItem(data.transportBrand);
    else if (index == _brand->currentIndex())
        _manufacturer->addItem(data.name);
}

void PurchaseWidget::handleCreatePurchase()
{
    auto user = _usersService->getUserByNumber(_currentUserNumber);
    auto manufacturer = _manufacturersService->getManufacturerByName(_manufacturer->currentText());

    TransportData data;
    data.brand = manufacturer.transportBrand;
    data.model = _model->text();
    data.price = 1000; //TODO
    data.guaranteePeriod = manufacturer.guaranteePeriod;
    data.year = _year->text().toInt();
    data.count = _count->text().toInt();
    data.condition = _condition->currentText();
    data.type = _type->currentText();
    data.inStock = false;
    data.receiptDate = QDateTime::currentDateTime()
                           .addDays(manufacturer.deliveryTime).toMSecsSinceEpoch();

    PurchaseData purchase;
    purchase.transportId = 0;
    purchase.count = _count->text().toInt();
    purchase.manufacturerId = manufacturer.id;
    purchase.userId = user.id;
    purchase.date = QDateTime::currentDateTime().toMSecsSinceEpoch();

    auto map = data.toDBMap();
    _transportService->addEntry(map);

    auto purchaseMap = purchase.toDBMap();
    _purchasesService->addEntry(purchaseMap);
}
