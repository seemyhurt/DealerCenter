#ifndef CORESERVICE_H
#define CORESERVICE_H

#include "iservice.h"

class CoreService : public IServiceT<CoreService>
{
    Q_OBJECT
public:
    CoreService(const QString &applicationName = "",
                QObject *parent = nullptr);

    QString applicationName() const;
    QString appDataPath() const;
    QString userDataPath() const;

    bool isFirtsStart();

private:
    QString _applicationName;
    QString _appDataPath;
    QString _userDataPath;
    static QString normalizePath(const QString path);
};

#endif // CORESERVICE_H
