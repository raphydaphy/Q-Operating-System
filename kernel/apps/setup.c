#include "setup.h"

// obviously this is not currnetly externally accessable data
// we can change this later when the data is more important to other apps
bool allowStatMonitor;
string userName;
string pcName;
string password;

void setup()
{
    messageBox("Welcome to Q OS. Press <RET> to begin\n\rthe setup process.");

    pcName = messageBox_I("Enter a name to assign to this\n\rcomputer.");
    userName = messageBox_I("Enter a username to assign to your\n\rQ OS user account.");

    password = messageBox_Pass("Enter a password to protect your\n\raccount");

    if(messageBox_YN("Allow Q OS to record information about\n\ryour computer?"))
    {
        allowStatMonitor = true;
    }

    print("Thanks for doing the setup. Here is your data:\n",yellow);

    print("Username: ",magenta);
    print(userName,red);

    print("\nPassword: ",magenta);
    print(password,red);
}
