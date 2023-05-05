#include "User.h"
void Login(vector<Person>& A, string& login_, vector<Person::Chat>& B)
{
    string Login;
    string Password;
    int n = 0;
    int k;
    cout << "Avtorization stage" << endl;
    cout << "Enter Login: ";
    cin >> Login;
    cout << endl;
    cout << "Enter Password: ";
    cin >> Password;
    cout << endl;
    for (int i = 0; i < A.size(); i++)
    {
        if (Login == A[i].login)
        {
            n++; // отмечаем, что такой логин есть
            k = i;
        }
    }
    try
    {
        if (n == 0) { throw bad_sing(); }
        else if (A[k].password == Password)
        {
            ChatMenu(A, B, Login);
        }
        else if (A[k].password != Password)
        {
            throw bad_sing();
        }

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}