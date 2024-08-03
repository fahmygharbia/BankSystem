#include <iostream>
#include "../Project 3 Bank System/clsLoginScreen.h"
using namespace std;

int main()
{

    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    return 0;
}