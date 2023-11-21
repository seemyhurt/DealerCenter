#include "coreservice.h"
#include <QDir>
#include <QStandardPaths>

CoreService::CoreService(const QString &applicationNameParam,
                         QObject *parent) : IServiceT<CoreService>(parent)
{
    _applicationName = applicationNameParam;

    _appDataPath = QDir::homePath() + QDir::separator();
    _userDataPath = _appDataPath;
#ifdef Q_OS_LINUX
    _appDataPath += ".";
    _appDataPath += _applicationName + QDir::separator();
    _appDataPath = QDir::toNativeSeparators(_appDataPath);
#endif

#ifdef Q_OS_WIN
    QDir tmp(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    tmp.cdUp();
    _appDataPath = tmp.absolutePath();
    _appDataPath += QDir::separator() +_applicationName + QDir::separator();
    _appDataPath = normalizePath(_appDataPath);
#endif

    _userDataPath += _applicationName + QDir::separator();
    _userDataPath += QString("Data") + QDir::separator();
    _userDataPath = normalizePath(_userDataPath);

    QDir d;
    d.mkpath(_appDataPath);
    d.mkpath(_userDataPath);

#ifdef Q_OS_UNIX
        QFile f(_configsPath);
        f.setPermissions(f.permissions() |
                         QFileDevice::ReadOther | QFileDevice::WriteOther | QFileDevice::ExeOther);
#endif

}

QString CoreService::userDataPath() const
{
    return _userDataPath;
}

QString CoreService::appDataPath() const
{
    return _appDataPath;
}

QString CoreService::applicationName() const
{
    return _applicationName;
}

QString CoreService::normalizePath(const QString path)
{
    return QDir::toNativeSeparators(QDir::cleanPath(path)) + QDir::separator();
}
