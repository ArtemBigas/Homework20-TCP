#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных в байтах, максимальный размер сообщения. tCP позволяет 1640
#define PORT 7777 // Будем использовать этот номер порта

int MakeSockert();

struct Person
{
    string login;
    string password;
    struct Chat {
        string Namefrom;
        string Nameto;
        string Message;
        Chat(const string& namefrom_, string& nameto_, string& message_) :Namefrom(namefrom_), Nameto(nameto_), Message(message_) {}
    };
    Person(const string& login_, string& password_) : login(login_), password(password_) {}

};
void ChatMenu(vector<Person>& A, vector<Person::Chat>& B, string& login_);
void  Registration(vector<Person>& A);
void  Login(vector<Person>& A, string& login_, vector<Person::Chat>& B);
void StartMenu(vector<Person>& A, string& login_, vector<Person::Chat>& B);
void GetLogAndPass(vector<Person>& A);
void GetMessage(vector<Person::Chat>& B);
void Send_Message(string message);//Функция отправки данных

class bad_sing : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "The wrong login or password";
        std::cout << std::endl;
    }
};
#endif