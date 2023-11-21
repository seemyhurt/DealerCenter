#ifndef APPMENU_H
#define APPMENU_H

#include <QMenuBar>

enum class Interface
{
    Unknown,
    Customer,
    Manager,
    Administrator
};

struct AppInterface
{
    Interface state;

    static AppInterface fromString(const QString & condition)
    {
        AppInterface tmp;
        if (condition == QLatin1String("Customer"))
            tmp.state = Interface::Customer;
        else if (condition == QLatin1String("Manager"))
            tmp.state = Interface::Manager;
        else if (condition == QLatin1String("Administrator"))
            tmp.state = Interface::Administrator;
        else
            tmp.state = Interface::Unknown;
        return tmp;
    }

    QString toString() const
    {
        switch (state) {
        case Interface::Customer:
            return QStringLiteral("Customer");
        case Interface::Manager:
            return QStringLiteral("Manager");
        case Interface::Administrator:
            return QStringLiteral("Administrator");
        default:
            return QStringLiteral("Unknown");
        }
    }

    inline bool operator ==(const AppInterface & other)
    {
        return state == other.state;
    }

    inline bool operator !=(const AppInterface & other)
    {
        return state != other.state;
    }
};

class AppMenu : public QMenuBar
{
    Q_OBJECT

public:
    AppMenu(QWidget * parent = nullptr);

    void setState(const Interface state);

private slots:
    void handleAboutApp();
    void handleInterfaceChanged();

signals:
    void menuInterfaceChanged(const QString & interface);

private:
    AppInterface _currentState;
    QMenu * _appMenu;
    QMenu * _interfaceMenu;

};

#endif // APPMENU_H
