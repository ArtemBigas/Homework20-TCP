#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define MESSAGE_LENGTH 1024 // ћаксимальный размер буфера дл€ данных в байтах, максимальный размер сообщени€. tCP позвол€ет 1640
#define PORT 7777 // Ѕудем использовать этот номер порта

inline int socket_file_descriptor, connection;//инициализаци€ —окета
inline struct sockaddr_in serveraddress, client; //—труктура дл€ обработки адреса сетевого взаимодействи€


int MakeSockert()
{
    // —оздадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4, SOCK_STREAM - то что TCP, 0 - протокол по умолчанию

    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        return socket_file_descriptor;
    }

    // ”становим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");//вводим ip сервера, в данном случае локального
    // «ададим номер порта
    serveraddress.sin_port = htons(PORT);
    // »спользуем IPv4
    serveraddress.sin_family = AF_INET;
    // ”становим соединение с сервером
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

        std::vector<char> chars(login_.begin(), login_.end());//преобразование string в Char
        chars.push_back('\0');

        char* LogChar = &chars[0];


        ssize_t bytes = write(socket_file_descriptor, LogChar, sizeof(LogChar));
         //≈сли передали >= 0  байт, значит пересылка прошла успешно
          if (bytes >= 0) {
            cout << "Login send to the server successfully.!" << endl;
          };
        write(socket_file_descriptor, LogChar, sizeof(LogChar));
        cout << endl;


        cout << "Enter the Password: ";
        cin >> password_;

        //std::vector<char> chars(password_.begin(), password_.end());//преобразование string в Char
        //chars.push_back('\0');

        //char* PassChar = &chars[0];

        //ssize_t bytes = write(socket_file_descriptor, PassChar, sizeof(PassChar));
        // ≈сли передали >= 0  байт, значит пересылка прошла успешно
        //if (bytes >= 0) {
         //   cout << "Password send to the server successfully.!" << endl;
       // };
       // write(socket_file_descriptor, PassChar, sizeof(PassChar));
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

    std::vector<Person> User;//массив дл€ хранени€ логина и парол€
    
    string Log;
    string Pass;

    if (MakeSockert()!=-1)
    Registration(User, Log,  Pass);
   
    return 0;
};