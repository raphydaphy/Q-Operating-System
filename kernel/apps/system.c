#include "system.h"

void systemHelp(string cmd)
{
    print("\nThe argument you entered, ",0x4F);
    print(cmd,0x4F);
    print(" was not found.",0x4F);
	print("\nShowing help for system:",0x0F);
	newline();
	print("\nSystem Utility\nCurrently only able to reboot and halt system.\nHard shutdown to power off.\n\nMenu:\n1. [reboot]\n2. [halt]\n3. [shutdown] ", 0x0F);
}

void system(string args)
{
	if (strEql(args," reboot"))
	{
		reboot();
	}
	else if (strEql(args," shutdown"))
	{
        shutdown();
    }
    else if (strEql(args," halt"))
    {
        halt();
    }
    else
    {
        systemHelp(args);
    }
}
