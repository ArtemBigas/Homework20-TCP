#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <cstring>
using namespace std;

#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных в байтах, максимальный размер сообщения. tCP позволяет 1640
#define PORT 7777 // Будем использовать этот номер порта

inline int socket_file_descriptor, connection;//инициализация Сокета
inline struct sockaddr_in serveraddress, client; //Структура для обработки адреса сетевого взаимодействия


int MakeSockert()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4, SOCK_STREAM - то что TCP, 0 - протокол по умолчанию

    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        return socket_file_descriptor;
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");//вводим ip сервера, в данном случае локального
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        cout << "Connection with the server failed.!" << endl;
        return connection;
    }
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
         
        ssize_t bytes = write(socket_file_descriptor, login_.c_str(), login_.size());
        //Если передали >= 0  байт, значит пересылка прошла успешно
        //char* LogChar;
        //LogChar = strcpy(new char[login_.length() + 1], login_.c_str());
        //ssize_t bytes = write(socket_file_descriptor, LogChar, sizeof(LogChar));
        if (bytes >= 0) {
            cout << "Login send to the server successfully.!" << endl;
        };
        //write(socket_file_descriptor, login_.c_str(), login_.size());
        //write(socket_file_descriptor, LogChar, sizeof(LogChar));
        cout << endl;
        

        cout << "Enter the Password: ";
        cin >> password_;

        cout << endl;

        bytes = write(socket_file_descriptor, password_.c_str(), password_.size());
        //char* PassChar;
        //PassChar = strcpy(new char[password_.length() + 1], password_.c_str());
        //bytes = write(socket_file_descriptor, PassChar, sizeof(PassChar));
        if (bytes >= 0) {
            cout << "Login send to the server successfully.!" << endl;
        };
        //write(socket_file_descriptor, password_.c_str(), password_.size());
        //write(socket_file_descriptor, PassChar, sizeof(PassChar));
        cout << endl;
        
        cout << endl;
        cout << login_ << endl << password_;//вывод отправляемых данных
        
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

    if (MakeSockert() != -1)
        Registration(User, Log, Pass);
    cin >> Log;

    return 0;
};