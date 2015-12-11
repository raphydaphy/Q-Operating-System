#include "setup.h"

void setup()
{
    clearLine(0,26,0x66);

    // show a small title to let the user know what they are doing
    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Q OS Setup Process", desc_foreground, 21, 9);

    messageBox("Welcome to Q OS. Press <RET> to begin\n\rthe setup process.");

    // get the user ot enter a PC-NAME and UserName for there Q OS Account
    pcName = messageBox_I("Enter a name to assign to this\n\rcomputer.");
    userName = messageBox_I("Enter a username to assign to your\n\rQ OS user account.");

    // get the user to enter a password to protect there account on Q OS
    password = messageBox_Pass("Enter a password to protect your\n\raccount");

    // this is mostly just a proof of concpet nad does nothing except ask a question for now
    if(messageBox_YN("Allow Q OS to record information about\n\ryour computer?"))
    {
        allowStatMonitor = true;
    }

    // require the user to login with their new account
    loggedIn = false;
    logout();
}
