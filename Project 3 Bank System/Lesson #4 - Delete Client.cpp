#include <iostream>
#include "clsBankClient.h"
#include "../clsInputValidate.h"
using namespace std;

void DeleteClient()
{
    string AccountNumber = "";
    cout << "Please enter account number: \t";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    char Answer = 'n';
    cout << "\nAre you sure you want to delete this client y/n? \t";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        if (Client.Delete())
        {
            cout << "\nClient Deleted Successfully :-)\n";
            Client.Print();
        }
        else
        {
            cout << "\nError Client Was not Deleted\n";
        }
    }
}

int main()
{
    DeleteClient();

    return 0;
}