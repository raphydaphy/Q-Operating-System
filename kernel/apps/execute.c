#include "execute.h"

void execute()
{
	print("\ntype>  ", white);
	readStr(executeContents, EXECUTESIZE, false);
	//Entering ? will allow for the user to see all of the available execute commands. Once the line gets long, we can put them in groups.
	if(streql(executeContents,"?")) {
		//All of the else if statments to follow should have an entry here.
		print("\n\"repeat\"=>  prints the next line over and over again, forever.", white);
		print("\n\"q\"=>  Asks for a Q-Compiler, then does nothing with it.", white);
	}
	// One day this else-if statement will take up thousands of lines (hopefully :D)
	else if(streql(executeContents,"repeat"))
	{
		print("\nrepeat>  ", white);
		readStr(executeContents, EXECUTESIZE, false);
		writing = 1;
		while(true)
		{
			newline();
			print(executeContents, white);
		}
	}
	else if(streql(executeContents,"q"))
	{
		print("\nQ-Compiler>  ",white);
		readStr(executeContents, EXECUTESIZE, false);
	}
	else
	{
		newline();
		print("The 'execute' command does not support the command you entered or it does not exist ", white);
	}
}
