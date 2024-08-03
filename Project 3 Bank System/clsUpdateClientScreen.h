#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

public:
    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t Update Client Screen");

        string AccountNumber = "";
        cout << "Please enter account number \t";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "Update Client Info \n";
        cout << "____________________________\n";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client);
            break;

        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};