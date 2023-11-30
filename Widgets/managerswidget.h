#ifndef MANAGERSWIDGET_H
#define MANAGERSWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
class ManufacturersModel;

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
    QSharedPointer<ManufacturersModel> _manufacturersModel;
};

#endif // MANAGERSWIDGET_H
