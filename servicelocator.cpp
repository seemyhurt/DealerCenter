#include "servicelocator.h"

ServiceLocator ServiceLocator::_serviceLocator;

ServiceLocator::ServiceLocator()
{

}

ServiceLocator::~ServiceLocator()
{
    clear();
}

void ServiceLocator::clear()
{
    _serviceLocator.serviceData.clear();
}
