#include "execute.h"

#include "../inc/intTypeDefs.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"

#ifndef EXECUTESIZE
#define EXECUTESIZE 1024
#endif
void execute()
{
	print("\ntype>  ", 0x0F);
	readStr(executeContents, EXECUTESIZE);
	if(strEql(executeContents,"repeat"))
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

	// One day this else-if statement will take up thousands of lines (hopefully :D)
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
