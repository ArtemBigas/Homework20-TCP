#include "User.h"
void ChatMenu(vector<Person>& A, vector<Person::Chat>& B, string& login_)
{
    char operat = '0';

    string Sender = login_;
    cout << "Your name: " << Sender << endl;


    string Receiver;
    string Message;
    bool k = false;//счетчик наличия введеного пользователя в списке зарегистрированных
    bool n = false;//счетчик наличия сообщений в истории
    bool m = false;//счетчик окончания чата
    while (operat != '3')
    {
        cout << "Choose a number: " << endl << "1 - to write text" << endl << "2 - History " << endl << "3 - Exit to the main Menu" << endl;
        cin >> operat;

        switch (operat)
        {
        case '1':
            cout << "if you want to finish Chat, send message 'end'" << endl;
            while (m == false) {
                Send_Message(Sender);
                cout << "Choose a reciever:";
                cin >> Receiver;
                for (int i = 0; i < A.size(); ++i)
                {
                    if (A[i].login == Receiver)
                    {
                        k = true;
                    };
                };
                    if (k == true)
                    {
                        Send_Message(Receiver);
                        cout << "Enter a message:";
                        cin >> Message;
                        Send_Message(Message);
                        if (Message == "end") { m = true;  break; };
                        GetMessage(B);
                    };
                    
                    
                 
            };
            if (k == false) cout << "Данный получатель незарегистрирован" << endl;
            k = false;
            break;
        case '2':
            cout << "Choose receiver-2:" << endl;
            for (int i = 0; i < A.size(); ++i)
            {
                cout << A[i].login << endl;
            }
            cin >> Receiver;

            for (int i = 0; i < A.size(); ++i)
            {
                if (A[i].login == Receiver)
                {
                    k = true;
                    for (int i = 0; i < B.size(); ++i)
                    {
                        if (Sender == B[i].Namefrom || Receiver == B[i].Nameto)
                        {
                            if (Receiver == B[i].Namefrom || Receiver == B[i].Nameto)
                            {
                                bool n = true;
                                cout << "Sender: " << B[i].Namefrom << " Receiver: " << B[i].Nameto << endl << " Text: " << B[i].Message << endl;
                            };
                        };
                    }
                };

            };
            if (k == false) cout << "This receiver is not registered" << endl;
            if (n == false) cout << "No history" << endl;
            k = false;
            break;
        default:

            std::cout << "You entered wrong number" << std::endl;
            std::cout << std::endl;
            break;

        };


    };
};