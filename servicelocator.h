#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include <QSharedPointer>

class IService;
/**
 * @brief The ServiceLocator class Совокупность сервисов
 */
class  ServiceLocator
{
    ServiceLocator();

public:
    ~ServiceLocator();

    /**
     * @brief Получение сервиса наследника IService<T>
     */
    template<class T>
    static QSharedPointer<T> service()
    {
        QSharedPointer<IService> res = _serviceLocator.serviceData.value(T::baseKey());
        if (res)
            return res.objectCast<T>();
        return  QSharedPointer<T>();
    }

    /**
     * @brief addService Добавление нового сервиса
     * @param service Объект сервиса
     * @return true сервис успешно добавлен
     */
    template<class T>
    static bool addService(QSharedPointer<T> service)
    {
        static_assert(std::is_base_of<IService, T>::value, "Class T not inherited from IService");
        const auto name = T::baseKey();
        if (service && !_serviceLocator.serviceData.contains(name))
        {
            _serviceLocator.serviceData.insert(name, service);
            return true;
        }
        return false;
    }
    /**
     * @brief clear удаление сервисов
     */
    static void clear();

private:
    QHash<QString, QSharedPointer<IService>> serviceData;
    static ServiceLocator _serviceLocator;
};

#endif // SERVICELOCATOR_H
