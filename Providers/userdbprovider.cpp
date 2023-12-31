#include "userdbprovider.h"
#include "../Common/userdata.h"
#include "../Services/servicelocator.h"
#include "../Services/coreservice.h"

UserDBProvider::UserDBProvider(QObject* parent) :
    LocalDBProviderBase{parent}
{
    setContext("user_data",
               UserData::dBKeys(),
               "users.db3",
               ServiceLocator::service<CoreService>()->appDataPath(),
               "UserDBProvider");
}

QVector<UserData> UserDBProvider::getUsers()
{
    using UD = UserData;
    using std::make_pair;

    return getAllElements(make_pair("id", &UD::id),
                          make_pair("phoneNumber", &UD::phoneNumber),
                          make_pair("firstName", &UD::firstName),
                          make_pair("lastName", &UD::lastName),
                          make_pair("patronymic", &UD::patronymic),
                          make_pair("age", &UD::age),
                          make_pair("type", &UD::type),
                          make_pair("password", &UD::password));
}

QString UserDBProvider::baseKey()
{
    return "UserDBProvider";
}

