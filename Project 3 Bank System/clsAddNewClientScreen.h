#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        cout << "Enter First Name     \t";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "Enter Last Name      \t";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "Enter Email          \t";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "Enter Phone          \t";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "Enter Pin Code        \t";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "Enter Account Balance \t";
        Client.SetAccountBalance(clsInputValidate::ReadDblNumber());
    }

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
    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Add New Client Screen");
        
        string AccountNumber = "";
        cout << "Please enter account number \t";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(NewClient);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
    }
};