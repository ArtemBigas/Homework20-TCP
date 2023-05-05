#include "User.h"
#include "MakeSockert.h"
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
void GetLogAndPass(vector<Person>& A) // Прием от Сервера регистрационных данных
{
    string Login;
    string Password;
    cout << "Client is waiting Login and Password from Server" << endl;
    std::string output_Log(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Логина от Сервера
    read(socket_file_descriptor, &output_Log[0], MESSAGE_LENGTH - 1); //read высчитывает строку размером MESSAGE_LENGTH, начиная от нулевого

    string Buffer_Log;// буферная переменная для получения Логина
    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Log[i] != 0) {
            cout << output_Log[i] << " ";
            Login.push_back((char)output_Log[i]);
        }
        else {
            break;
        };
    }; cout << endl;

    
    cout << endl;
    //cout << "Login received from client: " << login_ << endl;

    std::string output_Pass(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Пароля от Сервера
    read(socket_file_descriptor, &output_Pass[0], MESSAGE_LENGTH - 1);


    
    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Pass[i] != 0) {
            cout << output_Pass[i] << " ";
            Password.push_back((char)output_Pass[i]);
        }
        else {
            break;
        };
    }; cout << endl;

    
    cout << endl;
    cout << "Password received from client: " << Password << endl;


    A.emplace_back(Login, Password); // запись зарегистрированного клиента на сервере
};
void GetMessage(vector<Person::Chat>& B)
{
    cout << "Wait message" << endl;
    string Sender;// буферная переменная для получения Логина
    string Receiver;// буферная переменная для получения Пароля
    string Message;// буферная переменная для получения Сообщения
    std::string output_Sender(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Логина от Сервера
    read(socket_file_descriptor, &output_Sender[0], MESSAGE_LENGTH - 1); //read высчитывает строку размером MESSAGE_LENGTH, начиная от нулевого

    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Sender[i] != 0) {
            //cout << output_Sender[i] << " ";
            Sender.push_back((char)output_Sender[i]);
        }
        else
        {
            break;
        };
    }; cout << endl;
    //cout << endl;

    cout << "Sender received from client: " << Sender << endl;

    std::string output_Receiver(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Пароля от Сервера
    read(socket_file_descriptor, &output_Receiver[0], MESSAGE_LENGTH - 1);

    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Receiver[i] != 0) {
            //cout << output_Receiver[i] << " ";
            Receiver.push_back((char)output_Receiver[i]);
        }
        else {
            break;
        };
    }; cout << endl;
    //cout << endl;
    cout << "Receiver received from client: " << Receiver << endl;

    std::string output_Message(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Пароля от Сервера
    read(socket_file_descriptor, &output_Message[0], MESSAGE_LENGTH - 1);

    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Message[i] != 0) {
            //cout << output_Message[i] << " ";
            Message.push_back((char)output_Message[i]);
        }
        else {
            break;
        };
    }; cout << endl;
    //cout << endl;
    cout << "Message received from client: " << Message << endl;

    B.emplace_back(Sender, Receiver, Message); // запись зарегистрированного клиента на сервере
};
void Send_Message(string message)
{
    ssize_t bytes = write(socket_file_descriptor, message.c_str(), message.size());//c_str() переделывает string в const char*
    //Если передали >= 0  байт, значит пересылка прошла успешно

    if (bytes >= 0) {
        //cout << "Message send to the server successfully.!" << message << endl;
    };
    cout << endl;
};

