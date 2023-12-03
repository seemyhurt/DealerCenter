#ifndef MANAGERSWIDGET_H
#define MANAGERSWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class ManufacturersTableWidget;
class TransportTableWidget;

class ManagersWidget : public QWidget
{
    Q_OBJECT
public:
    ManagersWidget(QWidget * parent = nullptr);

    bool loginManager();

private slots:
    void handleCreatePurchase();

private:
    QSharedPointer<UserDBService> _service;
    QSharedPointer<ManufacturersTableWidget> _manufacturersWidget;
    QSharedPointer<TransportTableWidget> _transportsWidget;
};

#endif // MANAGERSWIDGET_H
