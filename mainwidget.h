#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class AppMenu;
class CustomerWidget;
class AdministratorWidget;
class QLayout;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private slots:
    void handleNeedChangeInterface(const QString & type);

private:
    QSharedPointer<AppMenu> _menu;
    QSharedPointer<CustomerWidget> _customerWidget;
    QSharedPointer<AdministratorWidget> _administratorWidget;
    QWidget * _lastAddedWidet = nullptr;

    QSharedPointer<QLayout> _currentLayout;
};

#endif // MAINWIDGET_H
