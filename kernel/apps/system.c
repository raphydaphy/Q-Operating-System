#include "system.h"

//Developer Names

void systemHelp(string cmd)
{
    print("\nThe argument you entered, ",0x4F);
    print(cmd,0x4F);
    print(" was not found.",0x4F);
	  print("\nShowing help for system:",white);
    newline();
    print("\nSystem Utility\nCurrently only able to reboot and halt system.\nHard shutdown to power off.\n\nMenu:\n1. [reboot]\n2. [halt]\n3. [shutdown] ", white);
}

void system(string args)
{
	if (streql(splitArg(args, 1),"reboot"))
    {
		reboot();
    }
	else if (streql(splitArg(args, 1),"shutdown"))
    {
        shutdown();
    }
  else if (streql(splitArg(args, 1),"halt"))
    {
        halt();
    }
  else if (streql(splitArg(args, 1),"about"))
    {
        print("\n Q Operating System \nVersion: 0.06 Alpha\n", 0xCF);
        //You might wanna replace your slack name with your full name (Its in alphabetical order)
        print("\nDevelopers:\n",white);
        print("- barteks2x\n",white);
        print("- Patrick van Duyse\n",white);
        print("- Plankp T\n",white);
        print("- raph\n",white);
        print("- Stanislaus Krisna\n",white);//stnkrisna
        print("- Talip Goeksu",white);
    }
  else
    {
        systemHelp(args);
    }
}
