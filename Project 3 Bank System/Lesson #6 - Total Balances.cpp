#include <iostream>
#include <vector>
#include <iomanip>
#include "clsBankClient.h"
#include "../clsInputValidate.h"
#include "../clsUtil.h"

void PrintClientRecordBalanceLine(clsBankClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.GetAccountBalance();
}

void ShowTotalBalance()
{
    vector<clsBankClient> vClients = clsBankClient::GetClientsList();

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n________________________________________________________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n________________________________________________________________________________________________\n\n";

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }

    else
    {
        for (clsBankClient &Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            cout << endl;
        }
    }

    cout << "\n________________________________________________________________________________________________\n\n";
    
    double TotalBalances = clsBankClient::GetTotalBalances();
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
    cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";

    cout << "\n________________________________________________________________________________________________\n\n";
}

int main()
{
    ShowTotalBalance();

    return 0;
}