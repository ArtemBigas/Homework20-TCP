#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define MESSAGE_LENGTH 1024 // ������������ ������ ������ ��� ������ � ������, ������������ ������ ���������. tCP ��������� 1640
#define PORT 7777 // ����� ������������ ���� ����� �����

inline int socket_file_descriptor, connection;//������������� ������
inline struct sockaddr_in serveraddress, client; //��������� ��� ��������� ������ �������� ��������������


int MakeSockert()
{
    // �������� �����
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);//AF_INET - IPv4, SOCK_STREAM - �� ��� TCP, 0 - �������� �� ���������

    if (socket_file_descriptor == -1) {
        cout << "Creation of Socket failed!" << endl;
        return socket_file_descriptor;
    }

    // ��������� ����� �������
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");//������ ip �������, � ������ ������ ����������
    // ������� ����� �����
    serveraddress.sin_port = htons(PORT);
    // ���������� IPv4
    serveraddress.sin_family = AF_INET;
    // ��������� ���������� � ��������
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

        std::vector<char> chars(login_.begin(), login_.end());//�������������� string � Char
        chars.push_back('\0');

        char* LogChar = &chars[0];


        ssize_t bytes = write(socket_file_descriptor, LogChar, sizeof(LogChar));
         //���� �������� >= 0  ����, ������ ��������� ������ �������
          if (bytes >= 0) {
            cout << "Login send to the server successfully.!" << endl;
          };
        write(socket_file_descriptor, LogChar, sizeof(LogChar));
        cout << endl;


        cout << "Enter the Password: ";
        cin >> password_;

        //std::vector<char> chars(password_.begin(), password_.end());//�������������� string � Char
        //chars.push_back('\0');

        //char* PassChar = &chars[0];

        //ssize_t bytes = write(socket_file_descriptor, PassChar, sizeof(PassChar));
        // ���� �������� >= 0  ����, ������ ��������� ������ �������
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

    std::vector<Person> User;//������ ��� �������� ������ � ������
    
    string Log;
    string Pass;

    if (MakeSockert()!=-1)
    Registration(User, Log,  Pass);
   
    return 0;
};