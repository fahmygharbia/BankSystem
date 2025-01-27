#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "../clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";
        cout << "Please enter account number: \t";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client y/n? \t";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};