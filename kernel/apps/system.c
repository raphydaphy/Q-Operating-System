#include "system.h"

//Developer Names

void systemHelp(string cmd)
{
    print("\nThe argument ", 0x4F);
    print(cmd, 0x4F);
    print(" was not found.", 0x4F);
    println("\nShowing help for system:",white);
    print("\nSystem Utility\nCurrently only able to reboot and halt system.\nHard shutdown to power off.\n\nMenu:\n1. [reboot]\n2. [halt]\n3. [shutdown] ", white);
}

void system(string args)
{
    args = splitArg(args, 1);
	if (streql(args, "reboot"))
    {
		reboot();
    }
	else if (streql(args, "shutdown"))
    {
        shutdown();
    }
    else if (streql(args, "halt"))
    {
        halt();
    }
    else if (streql(args, "about"))
    {
        print("\n Q Operating System\nVersion: 0.06 Alpha\n", 0xCF);
        //You might wanna replace your slack name with your full name (Its in alphabetical order)
        println("\nDevelopers:", white);
        println("- barteks2x", white);
        println("- Patrick van Duyse", white);
        println("- Plankp T", white);
        println("- raph", white);
        println("- Stanislaus Krisna", white);//stnkrisna
        print("- Talip Goeksu", white);
    }
    else
    {
        systemHelp(args);
    }
}
