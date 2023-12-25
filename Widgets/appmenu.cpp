#include "appmenu.h"
#include <QMenuBar>
#include <QCoreApplication>

AppMenu::AppMenu(QWidget * parent) :
    QMenuBar()
{ 
    _appMenu = addMenu("&App");
    _interfaceMenu = addMenu("&Interface");

    _appMenu->addAction("&About app", this, &AppMenu::handleAboutApp, Qt::CTRL + Qt::Key_Q);
    _appMenu->addAction("&Exit", QCoreApplication::instance(), &QCoreApplication::quit);

    _interfaceMenu->addAction("&Customer", this, &AppMenu::handleInterfaceChanged);
    _interfaceMenu->addAction("&Manager", this, &AppMenu::handleInterfaceChanged);
    _interfaceMenu->addAction("&Administrator", this, &AppMenu::handleInterfaceChanged);

    connect(_interfaceMenu, &QMenu::triggered, this, &AppMenu::handleInterfaceChanged);
}

void AppMenu::setState(const Interface state)
{
    _currentState.state = state;
}


void AppMenu::handleAboutApp()
{
    emit needShowHelp();
}

void AppMenu::handleInterfaceChanged()
{
    auto action = qobject_cast<QAction*>(sender());
    if (!action) return;

    auto state = AppInterface::fromString(action->text().remove(0, 1));
    if (state != _currentState)
        emit menuInterfaceChanged(state.toString());
}
