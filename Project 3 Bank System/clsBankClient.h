#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "../clsString.h"
#include "../clsInputValidate.h"
#include "../clsDate.h"
using namespace std;

//كتابة المسار بالكامل للوصول للملف من ملفات اخرى زى ملف Extention
const string FileNameClients = "E://My Programming Projects/C++/11 - OOP as it Should Be (Applications)/Project 3 Bank System/Clients.txt";
const string FileNameTransferLog = "E://My Programming Projects/C++/11 - OOP as it Should Be (Applications)/Project 3 Bank System/cTransferLog.txt";

class clsBankClient : public clsPerson
{
private:
    string _AccountNumber;
    string _PinCode;
    double _AccountBalance;
    bool _isMarkDelete = false;

    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;

public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        double srcBalanceAfter;
        double destBalanceAfter;
        string UserName;
    };

private:
    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector<string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClient = clsString::Split(Line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
    }

    static clsBankClient _GetEmptyObjectClient()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> _vClients;
        fstream MyFile;
        MyFile.open(FileNameClients, ios::in);

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                _vClients.push_back(_ConvertLinetoClientObject(Line));
            }
            MyFile.close();
        }
        return _vClients;
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";

        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

    static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open(FileNameClients, ios::out);
        if (MyFile.is_open())
        {
            string Line = "";
            for (clsBankClient &Client : vClients)
            {
                if (Client._isMarkDelete == false)
                {
                    Line = _ConverClientObjectToLine(Client);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient &_C : _vClients)
        {
            if (_C.AccountNumber() == AccountNumber())
            {
                _C = *this;
                break;
            }
        }
        _SaveCleintsDataToFile(_vClients);
    }

    void _AddDateLineToFile(string Line)
    {
        fstream MyFile;
        MyFile.open(FileNameClients, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << Line << endl;
        }
        MyFile.close();
    }

    void _AddNew(clsBankClient NewClient)
    {
        _AddDateLineToFile(_ConverClientObjectToLine(NewClient));
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";

        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        TransferLogRecord += UserName;

        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open(FileNameTransferLog, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber,
                  string PinCode, double AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    // __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(double AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    double GetAccountBalance()
    {
        return _AccountBalance;
    }

    // __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    /* void Print()
     {
         cout << "\nClient Card:";
         cout << "\n___________________";
         cout << "\nFirstName   : " << GetFirstName();
         cout << "\nLastName    : " << GetLastName();
         cout << "\nFull Name   : " << FullName();
         cout << "\nEmail       : " << GetEmail();
         cout << "\nPhone       : " << GetPhone();
         cout << "\nAcc. Number : " << _AccountNumber;
         cout << "\nPassword    : " << _PinCode;
         cout << "\nBalance     : " << _AccountBalance;
         cout << "\n___________________\n";
     }*/

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open(FileNameClients, ios::in);

        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObjectClient();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open(FileNameClients, ios::in);

        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyObjectClient();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExists = 2
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObject;
            break;

        case enMode::UpdateMode:

            _Update();
            return enSaveResults::svSucceeded;
            break;

        case enMode::AddNewMode:

            // This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }

            else
            {
                // We need to set the mode to update after add new
                _AddNew(*this);
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }

        return enSaveResults::svSucceeded;
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._isMarkDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(vClients);

        *this = _GetEmptyObjectClient();
        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        double TotalBalances = 0;

        for (clsBankClient &Client : vClients)
        {
            TotalBalances += Client.GetAccountBalance();
        }
        return TotalBalances;
    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
        return false;
    }

    bool Transfer(float Amount, clsBankClient &DestinationClient, string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;
    }

    static vector<stTrnsferLogRecord> GetTransfersLogList()
    {
        vector<stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open(FileNameTransferLog, ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;
            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }

            MyFile.close();
        }

        return vTransferLogRecord;
    }
};