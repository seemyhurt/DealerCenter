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
#include <QMessageBox>
#include <QSpinBox>
#include <QSet>

static QStringList getAvailableYears()
{
    static auto startYear = QDate(2000, 1, 1).year();
    static auto currentYear = QDate::currentDate().year();

    QStringList yearsList;
    yearsList.reserve(currentYear - startYear);
    for (int year = startYear; year <= currentYear; ++year)
        yearsList << QString::number(year);
    return yearsList;
}

PurchaseWidget::PurchaseWidget(const WidgetInterface interface, QWidget *parent) :
    QWidget(parent),
    _manufacturersService(ServiceLocator::service<ManufacturerDBService>()),
    _usersService(ServiceLocator::service<UserDBService>()),
    _transportService(ServiceLocator::service<TransportDBService>()),
    _purchasesService(ServiceLocator::service<PurchasesDBService>())
{
    bool isCustomerInterface = interface == WidgetInterface::Customer;

    auto lblType = new QLabel("&Transport type", this);
    _type = new QComboBox(this);
    lblType->setBuddy(_type);

    auto lblBrand = new QLabel("&Brand", this);
    _brand = new QComboBox(this);
    lblBrand->setBuddy(_brand);

    auto lblManufacturers = new QLabel("&Manufacturer", this);
    _manufacturer = new QComboBox(this);
    lblManufacturers->setBuddy(lblManufacturers);

    auto lblModel = new QLabel("&Model", this);
    if (isCustomerInterface)
    {
        _availableModels = new QComboBox(this);
        lblModel->setBuddy(_availableModels);
    }
    else
    {
        _model = new QLineEdit(this);
        lblModel->setBuddy(_model);
    }

    auto lblCondition = new QLabel("&Condition", this);
    _condition = new QComboBox(this);
    lblCondition->setBuddy(_condition);
    if (!isCustomerInterface)
        _condition->addItems({"New", "Old model", "Previously used"});

    auto lblYear = new QLabel("&Year", this);
    _availableYears = new QComboBox(this);
    lblYear->setBuddy(_availableYears);
    if (!isCustomerInterface)
        _availableYears->addItems(getAvailableYears());

    auto lblCount = new QLabel("&Count", this);
    _count = new QSpinBox(this);
    lblCount->setBuddy(_count);
    _count->setMaximum(100);
    _count->setMinimum(1);

    auto types = _manufacturersService->getAvailableTypes();
    if (!types.isEmpty())
        _type->addItems(types);

    connect(_type, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleTypeChanged);
    connect(_brand, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleBrandChanged);
    connect(_condition, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleConditionChanged);
    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &PurchaseWidget::handleManufacturerAdded);

    if (isCustomerInterface)
    {
        connect(_manufacturer, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleManufacturerChanged);
        connect(_availableModels, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleModelChanged);
    }
    auto buttonBuy = new QPushButton("Buy new car", this);
    connect(buttonBuy, &QPushButton::clicked, this, &PurchaseWidget::handleCreatePurchase);

    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(lblType, 0, 0);
    layout->addWidget(_type, 0, 1, 1, 4);
    layout->addWidget(lblBrand, 1, 0);
    layout->addWidget(_brand, 1, 1, 1, 4);
    layout->addWidget(lblManufacturers, 2, 0);
    layout->addWidget(_manufacturer, 2, 1, 1, 4);
    layout->addWidget(lblModel, 3, 0);
    isCustomerInterface ? layout->addWidget(_availableModels, 3, 1, 1, 4)
                        : layout->addWidget(_model, 3, 1, 1, 4) ;
    layout->addWidget(lblCondition, 4, 0);
    layout->addWidget(_condition, 4, 1, 1, 4);
    layout->addWidget(lblYear, 5, 0);
    layout->addWidget(_availableYears, 5, 1, 1, 4);
    layout->addWidget(lblCount, 6, 0);
    layout->addWidget(_count, 6, 1, 1, 4);
    layout->addWidget(buttonBuy, 7, 1, 1, 4);

    setLayout(layout);
    handleTypeChanged(_type->currentText());
    if (!isCustomerInterface)
        handleConditionChanged(_condition->currentText());
}

void PurchaseWidget::handleBrandChanged(const QString &brand)
{
    _manufacturer->clear();
    auto manufacturers = _manufacturersService->getManufacturersByBrand(brand);
    if (!manufacturers.isEmpty())
        _manufacturer->addItems(manufacturers);
}

void PurchaseWidget::handleTypeChanged(const QString &type)
{
    _brand->clear();
    auto brands = _manufacturersService->getManufacturersByType(type);
    if (!brands.isEmpty())
        _brand->addItems(brands);
}

void PurchaseWidget::handleManufacturerChanged(const QString &manufacturer)
{
    _availableModels->clear();
    auto models = _transportService->getManufacturersModels(manufacturer);
    if (!models.isEmpty())
        _availableModels->addItems(models);
}

void PurchaseWidget::handleConditionChanged(const QString &condition)
{
    _availableYears->clear();
    if (condition == QLatin1String("New"))
    {
        _availableYears->addItem(QString::number(QDate::currentDate().year()));
        _availableYears->setEnabled(false);
    }
    else
    {
        _availableYears->setEnabled(true);
        if (_usersService->getUserByNumber(_currentUserNumber).type == QLatin1String("Manager"))
            return _availableYears->addItems(getAvailableYears());

        auto key = _transportService->getTransportKey(_availableModels->currentText(), _manufacturer->currentText());
        auto transports = _transportService->getTransportBykey(key);

        QSet<int> years;
        for (const auto &transport : qAsConst(transports))
        {
            if (!years.contains(transport.year) && transport.condition == condition)
            {
                years.insert(transport.year);
                _availableYears->addItem(QString::number(transport.year));
            }
        }
    }
}

void PurchaseWidget::handleManufacturerAdded(const ManufacturerData & data)
{
    auto index = _type->findText(data.type);
    if (index == -1)
        _type->addItem(data.type);
    else if (index == _type->currentIndex())
        handleTypeChanged(data.type);
}

void PurchaseWidget::handleModelChanged(const QString &model)
{
    _condition->clear();
    auto key = _transportService->getTransportKey(model, _manufacturer->currentText());
    auto transports = _transportService->getTransportBykey(key);

    QSet<QString> conditions;
    _condition->clear();
    for (const auto &transport : qAsConst(transports))
    {
        if (!conditions.contains(transport.condition))
        {
            conditions.insert(transport.condition);
            _condition->addItem(transport.condition);
        }
    }
}

void PurchaseWidget::handleCreatePurchase()
{
    auto user = _usersService->getUserByNumber(_currentUserNumber);
    auto manufacturer = _manufacturersService->getManufacturerByName(_manufacturer->currentText());

    TransportData data;
    data.manufacturer = manufacturer.name;
    data.model = _model->text();
    data.year = _availableYears->currentText().toInt();
    data.count = _count->text().toInt();
    data.condition = _condition->currentText();

    auto date = QDateTime::currentDateTime().addDays(manufacturer.deliveryTime);
    data.inStock = date.date() == QDate::currentDate();
    data.receiptDate = date.toMSecsSinceEpoch();

    auto map = data.toDBMap();
    if (_transportService->addEntry(map).type() != QSqlError::NoError)
    {
        QMessageBox::warning(this, "Error", "Failed to create transport");
        return;
    }

    PurchaseData purchase;
    purchase.transportId = _transportService->getInsertTransportId();
    purchase.count = _count->text().toInt();
    purchase.manufacturerId = manufacturer.id;
    purchase.userId = user.id;
    purchase.date = QDateTime::currentDateTime().toMSecsSinceEpoch();

    auto purchaseMap = purchase.toDBMap();
    if (_purchasesService->addEntry(purchaseMap).type() != QSqlError::NoError)
        QMessageBox::warning(this, "Error", "Failed to create purchase");
}
