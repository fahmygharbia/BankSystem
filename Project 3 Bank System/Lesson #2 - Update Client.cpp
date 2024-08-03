#include <iostream>
#include "clsBankClient.h"
#include "../clsInputValidate.h"
using namespace std;

void ReadClientInfo(clsBankClient &Client)
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

void UpdateClient()
{
    string AccountNumber = "";
    cout << "Please enter account number \t";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    cout << "Update Client Info \n";
    cout << "____________________________\n";
    ReadClientInfo(Client);

    clsBankClient::enSaveResults SaveResult = Client.Save();

    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
        cout << "\nAccount Updated Successfully :-)\n";
        Client.Print();
        break;

    case clsBankClient::enSaveResults::svFaildEmptyObject:
        cout << "\nError account was not saved because it's Empty";
        break;
    }
}

int main()
{
    UpdateClient();

    return 0;
}
