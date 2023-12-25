#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class AppMenu;
class CustomerWidget;
class AdministratorWidget;
class ManagersWidget;
class QLabel;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private slots:
    void handleNeedChangeInterface(const QString & type);
    void handleSetUserInterface();
    void handleNeedShowHelp();

private:
    AppMenu * _menu;
    CustomerWidget * _customerWidget;
    AdministratorWidget * _administratorWidget;
    ManagersWidget * _managerWidget;
    QLabel * _help;

    QWidget * _lastAddedWidet = nullptr;
};

#endif // MAINWIDGET_H
