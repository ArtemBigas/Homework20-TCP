#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных в байтах, максимальный размер сообщения. tCP позволяет 1640
#define PORT 7777 // Будем использовать этот номер порта

struct sockaddr_in serveraddress, client;
socklen_t length;
int sockert_file_descriptor, connection, bind_status, connection_status;


int MakeSockert()
{// Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1) {
        cout << "Socket creation failed.!" << endl;
        return sockert_file_descriptor;
    };
    // 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Socket binding failed.!" << endl;
        return bind_status;
    }
    // Поставим сервер на прием данных 
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1) {
        cout << "Socket is unable to listen for new connections.!" << endl;
        return connection_status;
    }
    else {
        cout << "Server is listening for new connection: " << endl;//Сервер ждет соединения по порту 7777
    }
    length = sizeof(client);
    connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {
        cout << "Server is unable to accept the data from client.!" << endl;
        return connection;
    };
};

struct Person
{
    string login;
    string password;

    Person(string login_, string password_) : login(login_), password(password_) {}
};

class bad_sing : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "wrong number";
        std::cout << std::endl;
    }
};
void GetLogAndPass(vector<Person>& A, string login_, string password_) // Прием от Клиента регистрационных данных
{
    char* LogChar;
    char* PassChar;
    read(connection, LogChar, sizeof(LogChar));
    cout << "Login received from client: " << LogChar << endl;
   // read(connection, PassChar, sizeof(PassChar));
    //cout << "Password received from client: " << PassChar << endl;
    
    string L(LogChar, sizeof(LogChar));     //Конвертация Char в String
    string P(PassChar, sizeof(PassChar));
    login_ = L;
    password_ = P;
   
    A.emplace_back(login_, password_); // запись зарегистрированного клиента на сервере
};
void Registration(vector<Person>& A, string login_, string password_)
{
    cout << "Registration stage" << endl;

    cout << "Enter your Username: ";
    cin >> login_;
    try
    {
        for (int i = 0; i < A.size(); i++)
        {
            if (login_ == A[i].login)
            {
                throw "The same login is already registered!";
            }
        }

        cout << endl;


        cout << "Enter the Password: ";
        cin >> password_;

        cout << endl;

        A.emplace_back(login_, password_);


    }
    catch (const char* exception)
    {
        std::cout << std::endl;
        std::cout << exception << std::endl;
        std::cout << std::endl;
    }

}

int main()
{

    std::vector<Person> User;//массив для хранения логина и пароля

    string Log;
    string Pass;

    MakeSockert();
    GetLogAndPass(User, Log, Pass);
    Registration(User, Log, Pass);

    return 0;
};