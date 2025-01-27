#ifndef CLS_LOGIN_SCREEN_H
#define CLS_LOGIN_SCREEN_H

#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsMainScreen.h"
#include "clsGlobal.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFaild = false;
        string Username, Password;
        short FaildLoginCount = 0;

        do
        {

            if (LoginFaild)
            {
                FaildLoginCount++;
                cout << "\nInvlaid Username/Password!";
                cout << "\nYou have " << (3 - FaildLoginCount) << " Trial(s) to login.\n\n";
            }

            if (FaildLoginCount == 3)
            {
                cout << "\nYour are Locked after 3 faild trails \n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        // system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }
};


#endif // CLS_LOGIN_SCREEN_H