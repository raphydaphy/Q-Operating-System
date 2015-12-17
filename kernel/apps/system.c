#include "system.h"

void system(string args)
{
    args = splitArg(args, 1);
	if (streql(args, "REBOOT"))
    {
        if(messageBox_YN("Do you really want to reboot your\n\rcomputer?") == 1)
        {
		    reboot();
        }
    }
	else if (streql(args, "SHUTDOWN"))
    {
        if(messageBox_YN("Are you sure you want to shutdown\n\ryour computer?") == 1)
        {
            shutdown();
        }
    }
    else if (streql(args, "HALT"))
    {
        if(messageBox_YN("This will indefinately suspend your\n\rcomputer. Are you sure?") == 1)
        {
            messageBox("\x01 Have a good life \x02");
            halt();
        }
    }
    else if (streql(args, "LOGOUT"))
    {
        logout();
    }
    else if (streql(args, "ABOUT"))
    {
        print("\nYou are using the Q Operating System\nYour Version: 0.06 Alpha\n", brown);

        print("Logged in as: ", green);
        print(userName, white);

        //You might wanna replace your slack name with your full name (Its in alphabetical order)
        println("\nDevelopers:", yellow);
        println("- barteks2x", cyan); // cyan for trusted
        println("- Patrick van Duyse", cyan); // cyan for trusted
        println("- Plankp T", light_green);// light green for a main contributer
        println("- Raph Hennessy", purple);// purple for owner :)
        println("- Stanislaus Krisna", light_green);//stnkrisna (main contributer)
        println("- Tedi Bear", brown); // brown for dead
        print("- Talip Goeksu", cyan); // cyan for trusted
    }
    else
    {
        println("\nShowing help for system:", white);
        print("Options:\n1. reboot\n2. halt\n3. shutdown\n4. logout\n5. about", white);
    }
}
