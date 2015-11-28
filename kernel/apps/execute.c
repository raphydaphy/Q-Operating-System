#include "execute.h"

void execute()
{
	print("\ntype>  ", 0x0F);
	readStr(executeContents, EXECUTESIZE);
	//Entering ? will allow for the user to see all of the available execute commands. Once the line gets long, we can put them in groups.
	if(strEql(executeContents,"?")) {
		//All of the else if statments to follow should have an entry here.
		print("\n\"repeat\"=>  prints the next line over and over again, forever.", 0x0F);
		print("\n\"q\"=>  Asks for a Q-Compiler, then does nothing with it.", 0x0F);
	}
	// One day this else-if statement will take up thousands of lines (hopefully :D)
	else if(strEql(executeContents,"repeat"))
	{
		print("\nrepeat>  ", 0x0F);
		readStr(executeContents, EXECUTESIZE);
		writing = 1;
		while(true)
		{
			newline();
			print(executeContents, 0x0F);
		}
	}
	else if(strEql(executeContents,"q"))
	{
		print("\nQ-Compiler>  ",0x0F);
		readStr(executeContents, EXECUTESIZE);
	}
	else
	{
		newline();
		print("The 'execute' command does not support the command you entered or it does not exist ", 0x0F);
	}
}
