#include "system.h"

//Developer Names

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
        print("\n Q Operating System \nVersion: 0.0.5 Alpha\n", 0xCF);
        //You might wanna replace your slack name with your full name (Its in alphabetical order)
        print("\nDevelopers:\n",0x0F);
        print("- barteks2x\n",0x0F);
        print("- patrickvanduyse\n",0x0F);
        print("- plankp\n",0x0F);
        print("- raph\n",0x0F);
        print("- Stanislaus Krisna\n",0x0F);//stnkrisna
        print("- Talip Göksu",0x0F);
    }
  else
    {
        systemHelp(args);
    }
}
