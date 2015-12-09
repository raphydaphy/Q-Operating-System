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
	if (streql(args," -h"))
		writerHelp();
	else
	{
		// this is called when someone types "writer" on the command line

		// Some good colors for background: 66, 88, 99, CC, EE
	    paintScreen(0x99);

	    // Made the intro beautiful
	    drawFrame(0x38, 0, 0, 80, 4);
	    printAt("                          Q OS Text Editor                                  \r\n", 0x39, 1, 1);
	    printAt("            A Simple Text Editor for Q OS by Raph Hennessy                    ",0x34,1,2);

	    newline();
	    newline();
	    newline();
		newline();
		
		writing = true;
		readStr(writerContents, WRITERSIZE);
		writing = false;
	}
}
