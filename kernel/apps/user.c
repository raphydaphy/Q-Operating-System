#include "user.h"

bool loggedIn = false;

void logout()
{
    loggedIn = false;
}

void login()
{
    while (!loggedIn)
    {
        string buffPassword = msgBox_Pass("Enter your password to unlock your account.");
        if(!streql(buffPassword,password))
        {
            msgBox("Invalid Password!");
        }
        else
        {
            loggedIn = true;
        }
    }
}
