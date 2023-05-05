#include "User.h"
#include "MakeSockert.h"

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
void GetLogAndPass(vector<Person>& A) // Прием от Клиента регистрационных данных
{
    string Login;// буферная переменная для получения Логина
    string Password;// буферная переменная для получения Пароля
    std::string output_Log(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Логина от Сервера
    read(connection, &output_Log[0], MESSAGE_LENGTH - 1); //read высчитывает строку размером MESSAGE_LENGTH, начиная от нулевого

    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Log[i] != 0) {
            //cout << output_Log[i] << " ";
            Login.push_back((char)output_Log[i]);
        }
        else {
            break;
        };
    }; cout << endl;
    cout << endl;

    //cout << "Login received from client: " << login_ << endl;

    std::string output_Pass(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Пароля от Сервера
    read(connection, &output_Pass[0], MESSAGE_LENGTH - 1);
  
    for (int i = 0; i < MESSAGE_LENGTH; i++) //удаляет из строки лишние 0 и присваивает значение строке login_
    {

        if ((int)output_Pass[i] != 0) {
            //cout << output_Pass[i] << " ";
            Password.push_back((char)output_Pass[i]);
        }
        else {
            break;
        };
    }; cout << endl;
    cout << endl;
    //cout << "Password received from client: " << password_ << endl;


    A.emplace_back(Login, Password); // запись зарегистрированного клиента на сервере
};
void GetMessage(vector<Person::Chat>& B)
{
    cout << "Wait message" << endl;
    string Sender;// буферная переменная для получения Логина
    string Receiver;// буферная переменная для получения Пароля
    string Message;// буферная переменная для получения Сообщения
    std::string output_Sender(MESSAGE_LENGTH, 0);// буферная переменная размера MESSAGE_LENGTH для получения Логина от Сервера
    read(connection, &output_Sender[0], MESSAGE_LENGTH - 1); //read высчитывает строку размером MESSAGE_LENGTH, начиная от нулевого

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
    read(connection, &output_Receiver[0], MESSAGE_LENGTH - 1);

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
        read(connection, &output_Message[0], MESSAGE_LENGTH - 1);

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
    ssize_t bytes = write(connection, message.c_str(), message.size());//c_str() переделывает string в const char*
    //Если передали >= 0  байт, значит пересылка прошла успешно

    if (bytes >= 0) {
        //cout << "Message send to the server successfully.!" << message << endl;
    };
    cout << endl;
};
