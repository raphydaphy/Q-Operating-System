#include "writer.h"

void writerHelp()
{
	newline();
	print("Showing help for writer:",0x0F);
	newline();
	print("A text buffer that does not store any text entered!",0x0F);
}

void writer(string args)
{
	if (strEql(args," -h"))
	{
		writerHelp();
	}
	else
	{
		// this is called when someone types "writer" on the command line

		clearScreen();
		print("================================================================================", 0x3F);
		print("                      Q OS Text Editor Version 0.2                              ", 0x3F);
		print("================================================================================", 0x3F);
		writing = true;
		readStr(writerContents, WRITERSIZE);
		writing = false;
	}
}
