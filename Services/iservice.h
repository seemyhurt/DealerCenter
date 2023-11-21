#ifndef ISERVICE_H
#define ISERVICE_H

#include <QObject>
#include <typeinfo>

/**
 * @brief Базовый интефейс для всех сервисов
 */
class IService : public QObject
{
    Q_OBJECT
public:
    explicit IService(QObject *parent = nullptr) : QObject(parent) {};

};

/**
 * @brief Шаблонный интефейс для всех сервисов
 */
template <class T>
class IServiceT : public IService
{
public:
    explicit IServiceT(QObject *parent = nullptr) : IService(parent) {}

    /**
     * @brief baseKey на основе шалона получаем строковое имя сервиса
     * @return имя сервиса
     */
    static QString baseKey() {return QString(typeid(T).name());}

};

#endif // ISERVICE_H
