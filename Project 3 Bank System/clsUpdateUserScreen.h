#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../clsInputValidate.h"
#include "clsUsers.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:
    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n?\t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow User List? y/n?               \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New User? y/n?                 \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete User? y/n?                  \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate User? y/n?                  \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind User? y/n?                    \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n?                   \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n?                   \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n?            \t";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pShowLoginRegister;
        }

        return Permissions;
    }

    static void _ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: \t";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName:  \t";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email:     \t";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone:     \t";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password:  \t";
        User.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permission:\t";
        User.SetPermissions(_ReadPermissionsToSet());
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.GetPhone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

public:
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t Update User Screen");

        cout << "Please Enter User Name \t";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "Update User Info \n";
        cout << "____________________________\n";
        _ReadUserInfo(User);

        clsUser::enSaveResults SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintUser(User);
            break;

        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};
