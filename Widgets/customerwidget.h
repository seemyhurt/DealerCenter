#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class UserDBService;
struct UserData;

class CustomerWidget : public QWidget
{
    Q_OBJECT
public:
    CustomerWidget(QWidget * parent = nullptr);

    bool loginCutomer();

private:
    bool registerUser();

private:
    QSharedPointer<UserDBService> _service;
};

#endif // CUSTOMERWIDGET_H
