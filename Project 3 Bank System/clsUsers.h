#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "../clsString.h"
#include "../clsInputValidate.h"
#include "../clsUtil.h"
using namespace std;

// كتابة المسار بالكامل للوصول للملف من ملفات اخرى زى ملف Extention
const string FileNameUsers = "E://My Programming Projects/C++/11 - OOP as it Should Be (Applications)/Project 3 Bank System/cUsers.txt";
const string FileNameLoginRegister = "E://My Programming Projects/C++/11 - OOP as it Should Be (Applications)/Project 3 Bank System/cLoginRegister.txt";
const short EncreyptionKey = 5;

class clsUser : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

public: // public to declear struct and use it
    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

private:
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;

        vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2], EncreyptionKey);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";

        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        // here we encypt store the encrypted Password not the real one.
        LoginRecord += clsUtil::EncryptText(_Password, EncreyptionKey) + Seperator;
        LoginRecord += to_string(_Permissions);

        return LoginRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUser = clsString::Split(Line, Seperator);
        return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptText(vUser[5], EncreyptionKey), stoi(vUser[6]));
    }

    static clsUser _GetEmptyObjectUser()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> _vUsers;
        fstream MyFile;
        MyFile.open(FileNameUsers, ios::in);

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                _vUsers.push_back(_ConvertLinetoUserObject(Line));
            }
            MyFile.close();
        }
        return _vUsers;
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string stUserRecord = "";

        stUserRecord += User.GetFirstName() + Seperator;
        stUserRecord += User.GetLastName() + Seperator;
        stUserRecord += User.GetEmail() + Seperator;
        stUserRecord += User.GetPhone() + Seperator;
        stUserRecord += User.GetUserName() + Seperator;
        // here we encypt store the encrypted Password not the real one.
        stUserRecord += clsUtil::EncryptText(User.GetPassword(), EncreyptionKey) + Seperator;
        stUserRecord += to_string(User.GetPermissions());

        return stUserRecord;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open(FileNameUsers, ios::out);
        if (MyFile.is_open())
        {
            string Line = "";
            for (clsUser &User : vUsers)
            {
                if (User._MarkedForDelete == false)
                {
                    Line = _ConverUserObjectToLine(User);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();

        for (clsUser &_C : _vUsers)
        {
            if (_C.GetUserName() == GetUserName())
            {
                _C = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddDateLineToFile(string Line, string FileNameUsers = "cUsers.txt")
    {
        fstream MyFile;
        MyFile.open(FileNameUsers, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << Line << endl;
        }
        MyFile.close();
    }

    void _AddNew()
    {
        _AddDateLineToFile(_ConverUserObjectToLine(*this));
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
            string Password, short Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pShowLoginRegister = 128
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    // __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }

    //  __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    //__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open(FileNameUsers, ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyObjectUser();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open(FileNameUsers, ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyObjectUser();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                // We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
        return enSaveResults::svSucceeded;
    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector<clsUser> _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.GetUserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyObjectUser();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->GetPermissions() == enPermissions::eAll)
            return true;

        if ((Permission & this->GetPermissions()) == Permission)
            return true;
        else
            return false;
    }

    void RegisterLogIn()
    {
        _AddDateLineToFile(_PrepareLogInRecord(), FileNameLoginRegister);
    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open(FileNameLoginRegister, ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            stLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }

            MyFile.close();
        }

        return vLoginRegisterRecord;
    }
};