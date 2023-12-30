#include "purchasewidget.h"
#include "../Services/servicelocator.h"
#include "../Services/manufacturerdbservice.h"
#include "../Services/userdbservice.h"
#include "../Services/purchasesdbservice.h"
#include "../Services/transportdbservice.h"
#include "../Common/manufacturerdata.h"
#include "../Common/purchasedata.h"
#include "../Common/transportdata.h"

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
    static const auto startYear = QDate(2000, 1, 1).year();
    static const auto currentYear = QDate::currentDate().year();

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

    auto lblPrice = new QLabel("&Price", this);
    _price = new QLineEdit(this);
    _price->setEnabled(false);
    lblPrice->setBuddy(_price);

    auto types = _manufacturersService->getAvailableTypes();
    if (!types.isEmpty())
        _type->addItems(types);

    connect(_type, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleTypeChanged);
    connect(_brand, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleBrandChanged);
    connect(_condition, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleConditionChanged);
    connect(_manufacturersService.data(), &ManufacturerDBService::manufacturerAdded, this, &PurchaseWidget::handleManufacturerAdded);
    connect(_manufacturer, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleManufacturerChanged);
    connect(_count, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &PurchaseWidget::handleRecheckWidgets);

    if (isCustomerInterface)
    {
        connect(_availableModels, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleModelChanged);
        connect(_purchasesService.data(), &PurchasesDBService::purchaseAdded, this, &PurchaseWidget::handlePurchaseAdded);
        connect(_availableYears, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleRecheckWidgets);

        _count->setEnabled(false);
        _count->setValue(0);
    }
    else
    {
        _count->setMaximum(100);
        _count->setMinimum(1);
        connect(_model, &QLineEdit::textChanged, this, &PurchaseWidget::handleRecheckWidgets);
    }

    _buttonBuy = new QPushButton("Make a purchase", this);
    connect(_buttonBuy, &QPushButton::clicked, this, &PurchaseWidget::handleCreatePurchase);

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

    if (isCustomerInterface)
    {
        auto lblDate = new QLabel("&Receipt date", this);
        _receiptDate = new QComboBox(this);
        lblDate->setBuddy(_price);

        connect(_receiptDate, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleRecalculateCount);
        connect(_availableYears, &QComboBox::currentTextChanged, this, &PurchaseWidget::handleRecalculateCount);

        layout->addWidget(lblDate, 6, 0);
        layout->addWidget(_receiptDate, 6, 1, 1, 4);
        layout->addWidget(lblCount, 7, 0);
        layout->addWidget(_count, 7, 1, 1, 4);
        layout->addWidget(lblPrice, 8, 0);
        layout->addWidget(_price, 8, 1, 1, 4);
        layout->addWidget(_buttonBuy, 9, 1, 1, 4);
    }
    else
    {
        layout->addWidget(lblCount, 6, 0);
        layout->addWidget(_count, 6, 1, 1, 4);
        layout->addWidget(lblPrice, 7, 0);
        layout->addWidget(_price, 7, 1, 1, 4);
        layout->addWidget(_buttonBuy, 8, 1, 1, 4);
    }

    setLayout(layout);
}

void PurchaseWidget::setCurrentUser(quint64 number)
{
    _currentUserNumber = number;
    handleTypeChanged(_type->currentText());
    if (_usersService->getUserByNumber(_currentUserNumber).type != QLatin1String("Customer"))
        handleConditionChanged(_condition->currentText());
    handleRecheckWidgets();
}

void PurchaseWidget::handleBrandChanged(const QString &brand)
{
    _manufacturer->clear();
    auto manufacturers = _manufacturersService->getManufacturersByBrand(brand);
    for (const auto &manufacturer : qAsConst(manufacturers))
    {
        auto type = _manufacturersService->getManufacturerByName(manufacturer).type;
        if (type == _type->currentText())
            _manufacturer->addItem(manufacturer);
    }
}

void PurchaseWidget::handleTypeChanged(const QString &type)
{
    _brand->clear();
    auto brands = _manufacturersService->getBrandsByType(type);
    if (!brands.isEmpty())
        _brand->addItems(brands);
}

void PurchaseWidget::handleManufacturerChanged(const QString &manufacturer)
{
    if (_currentUserNumber == 0)
        return;

    if (_usersService->getUserByNumber(_currentUserNumber).type == QLatin1String("Customer"))
    {
        _availableModels->clear();
        auto models = _transportService->getManufacturersModels(manufacturer);
        if (!models.isEmpty())
            _availableModels->addItems(models);
    }

    handleRecheckWidgets();
}

void PurchaseWidget::handleConditionChanged(const QString &condition)
{
    if (_currentUserNumber == 0)
        return;

    QList<TransportData> transports;

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
        transports = _transportService->getTransportByKey(key);

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

    if (_usersService->getUserByNumber(_currentUserNumber).type != QLatin1String("Customer"))
        return;

    auto key = _transportService->getTransportKey(_availableModels->currentText(), _manufacturer->currentText());
    _receiptDate->clear();
    if (transports.isEmpty())
        transports = _transportService->getTransportByKey(key);

    QSet<QString> dates;
    for (const auto &transport : qAsConst(transports))
    {
        if (transport.receiptDate == 0)
            continue;

        auto date = QDateTime::fromMSecsSinceEpoch(transport.receiptDate).toString("dd.MM.yyyy");
        if (!dates.contains(date) && transport.condition == condition)
        {
            dates.insert(date);
            _receiptDate->addItem(date);
        }
    }
}

void PurchaseWidget::handleManufacturerAdded(const ManufacturerData & data)
{
    auto emptyPart = _type->findText("");
    if (emptyPart != -1)
        _type->removeItem(emptyPart);

    auto index = _type->findText(data.type);
    if (index == -1)
        _type->addItem(data.type);
    else if (index == _type->currentIndex())
        handleTypeChanged(data.type);
}

void PurchaseWidget::handleModelChanged(const QString &model)
{
    auto key = _transportService->getTransportKey(model, _manufacturer->currentText());
    auto transports = _transportService->getTransportByKey(key);

    _condition->clear();
    _receiptDate->clear();

    QSet<QString> conditions; 
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
    data.year = _availableYears->currentText().toInt();
    data.count = _count->text().toInt();
    data.condition = _condition->currentText();

    auto date = QDateTime::currentDateTime().addDays(manufacturer.deliveryTime);
    data.receiptDate = date.toMSecsSinceEpoch();

    if (user.type == QLatin1String("Customer"))
    {
        data.model = _availableModels->currentText();
        if (!_transportService->modifyTransportData(data))
        {
            QMessageBox::warning(this, "Error", "Failed to create transport");
            return;
        }
    }
    else
    {
        data.model = _model->text();
        auto map = data.toDBMap();
        if (_transportService->addEntry(map).type() != QSqlError::NoError)
        {
            QMessageBox::warning(this, "Error", "Failed to create transport");
            return;
        }
    }

    PurchaseData purchase;
    purchase.transportId = _transportService->getInsertTransportId();
    purchase.count = _count->text().toInt();
    purchase.manufacturerId = manufacturer.id;
    purchase.userId = user.id;
    purchase.date = QDateTime::currentDateTime().toMSecsSinceEpoch();
    purchase.price = _price->text().toLongLong();

    auto purchaseMap = purchase.toDBMap();
    if (_purchasesService->addEntry(purchaseMap).type() != QSqlError::NoError)
        QMessageBox::warning(this, "Error", "Failed to create purchase");
}

void PurchaseWidget::recalculatePrice()
{
    if (_currentUserNumber == 0)
        return;

    auto manufacturer = _manufacturersService->getManufacturerByName(_manufacturer->currentText());
    if (_usersService->getUserByNumber(_currentUserNumber).type == QLatin1String("Customer"))
    {
        auto date = QDateTime::fromString(_receiptDate->currentText(), "dd.MM.yyyy");
        auto daysToReceipt = QDateTime::currentDateTime().daysTo(date);
        if (daysToReceipt == 0) daysToReceipt = 1;
        auto price  = manufacturer.basePrice * _count->value() * manufacturer.guaranteePeriod * 1 / daysToReceipt * (_availableYears->currentText().toInt() % 2000 + 1);
        _price->setText(QString::number(price));
    }
    else
        _price->setText(QString::number(manufacturer.basePrice * _count->value()));
}

void PurchaseWidget::handlePurchaseAdded(const PurchaseData &purchase)
{
    auto manufacturer = _manufacturersService->getManufacturerById(purchase.manufacturerId);
    auto index = _type->findText(manufacturer.type);
    if (index == _type->currentIndex())
        handleTypeChanged(manufacturer.type);
}

void PurchaseWidget::handleRecalculateCount()
{
    _count->setValue(0);
    auto count = getCurrentTransportCount();
    if (count != 0)
    {
        _count->setEnabled(true);
        _count->setMaximum(count);
    }
    else
        _count->setEnabled(false);
}

void PurchaseWidget::handleRecheckWidgets()
{
    if (_currentUserNumber == 0)
        return;

    if (_usersService->getUserByNumber(_currentUserNumber).type != QLatin1String("Customer"))
    {
        if (_model->text().isEmpty())
            _buttonBuy->setEnabled(false);
        else
            _buttonBuy->setEnabled(true);
    }
    else
    {
        if (_availableModels->currentText().isEmpty() ||
            _condition->currentText().isEmpty() ||
            _availableYears->currentText().isEmpty() ||
            _receiptDate->currentText().isEmpty() ||
            _count->value() == 0)
        {
            _buttonBuy->setEnabled(false);
        }
        else
            _buttonBuy->setEnabled(true);

    }
    recalculatePrice();
}

int PurchaseWidget::getCurrentTransportCount()
{
    auto key = _transportService->getTransportKey(_availableModels->currentText(), _manufacturer->currentText());
    auto transports = _transportService->getTransportByKey(key);

    quint64 date = QDateTime::fromString(_receiptDate->currentText(), "dd.MM.yyyy").toMSecsSinceEpoch();
    TransportData data {0,
                       _availableModels->currentText(),
                       _availableYears->currentText().toInt(),
                       0,
                       _condition->currentText(),
                       date,
                       _manufacturer->currentText()
    };

    for (const auto &transport : qAsConst(transports))
    {
        if (data == transport)
            return transport.count;
    }
    return 0;
}
