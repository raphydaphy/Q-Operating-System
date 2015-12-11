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
        string buffPassword = "";
        buffPassword = messageBox_Pass("Enter your password to unlock your\n\raccount.");

        if(!streql(buffPassword,password))
        {
            messageBox("Invalid Password!");
        }
        else
        {
            loggedIn = true;
        }
    }
}
