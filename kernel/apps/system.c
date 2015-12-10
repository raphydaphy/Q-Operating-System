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
        print("\nYou are using the Q Operating System\nYour Version: 0.06 Alpha\n", brown);
        //You might wanna replace your slack name with your full name (Its in alphabetical order)
        println("\nDevelopers:", yellow);
        println("- barteks2x", cyan);
        println("- Patrick van Duyse", cyan);
        println("- Plankp T", light_green);// light green for a main contributer
        println("- Raph Hennessy", purple);// purple for owner :)
        println("- Stanislaus Krisna", light_green);//stnkrisna (main contributer)
        print("- Talip Goeksu", cyan);
    }
    else
    {
        systemHelp(args);
    }
}
