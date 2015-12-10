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

    messageBox(password);

    if(messageBox_YN("Allow Q OS to record informaiton about\n\ryour computer?"))
    {
        allowStatMonitor = true;
    }
}

/*
messageBox("Hit <RET> to quit this and hit <Q> to\n\rleave");
messageBox_YN("Hit <Y> or <N> or <C> to quit this...");
messageBox_I("INPUT::::");
*/
