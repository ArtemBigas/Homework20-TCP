#include "User.h"
int main()
{
    std::vector<Person> User;//массив для хранения логина и пароля
    std::vector<Person::Chat> Messenger;//массив для хранения сообщений
    string Log;


    if (MakeSockert() != -1)
    {
        StartMenu(User, Log, Messenger);
    };

    return 0;
};