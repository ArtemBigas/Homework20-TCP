#include "User.h"
void  Registration(vector<Person>& A)
{
    string Login;
    string Password;
    cout << "Registration stage" << endl;
    cout << "Enter Login: ";
    cin >> Login;
    try
    {
        for (int i = 0; i < A.size(); i++)
        {
            if (Login == A[i].login)
            {
                throw "This Login already registered ";
            }
        }
        cout << endl;
        Send_Message(Login);
        cout << "Enter Password: ";
        cin >> Password;
        cout << endl;
        Send_Message(Password);
        A.emplace_back(Login, Password);
    }
    catch (const char* exception)
    {
        std::cout << std::endl;
        std::cout << exception << std::endl;
        std::cout << std::endl;
    }
}