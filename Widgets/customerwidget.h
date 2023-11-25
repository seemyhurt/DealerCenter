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

signals:
    void newUserRegistred();

private slots:
    void handleRegisterUser();

private:
    QSharedPointer<UserDBService> _service;
};

#endif // CUSTOMERWIDGET_H
