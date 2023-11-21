#ifndef IPROVIDER_H
#define IPROVIDER_H

#include <QObject>
#include <typeinfo>

namespace DatabaseCommon {

class IProvider : public QObject
{
    Q_OBJECT
public:
    explicit IProvider(QObject *parent = nullptr) : QObject(parent) {}
};

template <class T>
class IProviderT : public IProvider
{
public:
    explicit IProviderT(QObject *parent = nullptr) : IProvider(parent) {}

    /**
     * @brief baseKey на основе шаблона получаем строковое имя провайдера
     * @return имя сервиса
     */
    static QString baseKey() {return QString(typeid(T).name());}

};

}

#endif // IPROVIDER_H
