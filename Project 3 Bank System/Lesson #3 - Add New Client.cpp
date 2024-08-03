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

void AddNewClient()
{
    string AccountNumber = "";
    cout << "Please enter account number \t";
    AccountNumber = clsInputValidate::ReadString();

    while (clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number Is Already Used, Choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

    cout << "Add New Client\n";
    cout << "____________________________\n";
    ReadClientInfo(NewClient);

    clsBankClient::enSaveResults SaveResult = NewClient.Save();

    switch (SaveResult)
    {
    case clsBankClient::enSaveResults::svSucceeded:
        cout << "\nAccount Updated Successfully :-)\n";
        NewClient.Print();
        break;

    case clsBankClient::enSaveResults::svFaildEmptyObject:
        cout << "\nError account was not saved because it's Empty";
        break;

    case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        cout << "\nError account was not saved because account number is used!\n";
        break;
    }
}

int main()
{

    AddNewClient();

    return 0;
}
