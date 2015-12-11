#include "setup.h"

void setup()
{
    clearLine(0,26,0x66);

    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Q OS Setup Process", desc_foreground, 21, 9);

    messageBox("Welcome to Q OS. Press <RET> to begin\n\rthe setup process.");

    pcName = messageBox_I("Enter a name to assign to this\n\rcomputer.");
    userName = messageBox_I("Enter a username to assign to your\n\rQ OS user account.");

    password = messageBox_Pass("Enter a password to protect your\n\raccount");

    if(messageBox_YN("Allow Q OS to record information about\n\ryour computer?"))
    {
        allowStatMonitor = true;
    }

    loggedIn = false;
    logout();
}
