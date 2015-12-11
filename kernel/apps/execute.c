#include "execute.h"

int repeatUntilKey(int key,string repeatText)
{
    while(true)
    {
		newline();
		print(repeatText,yellow);
        // if a key is presesd
        if(inportb(0x64) & 0x1)
        {
            uint8 value = inportb(0x60);
			if(value == key)
			{
				return key;
			}
        }
    }
}

void execute(string args)
{
	//Entering ? will allow for the user to see all of the available execute commands. Once the line gets long, we can put them in groups.
	if(streql(splitArg(args, 1),"-h"))
	{
		//All of the else if statments to follow should have an entry here.
		print("\n\"repeat\" =>  Prints the next line over and over again until <ESC> is pressed", green);
		print("\n\"q\"      =>  Asks for a Q-Compiler, then does nothing with it.", green);
	}
	else if(streql(splitArg(args, 1),"repeat"))
	{
		writing = 1;
		repeatUntilKey(0x01,splitArg(args, 2));
		writing = 0;
	}
	else if(streql(executeContents,"q"))
	{
		if (streql(splitArg(args, 2),"") || streql(splitArg(args, 2)," "))
		{
			print("\nYou must include the Q Code to be executed after the executeable type",red);
		}
		else
		{
			// need to compile some Q Code here :)
		}
	}
	else
	{
		newline();
		print("The 'execute' command does not support the executable type you specified", red);
	}
}
