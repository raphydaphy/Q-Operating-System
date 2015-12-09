#include "writer.h"

void writerHelp()
{
	newline();
	print("Showing help for writer:",white);
	newline();
	print("A text buffer that does not store any text entered!",white);
}

void writer(string args)
{
	if (streql(args," -h"))
		writerHelp();
	else
	{
		// this is called when someone types "writer" on the command line

		// Some good colors for background: 66, 88, 99, CC, EE
	    paintScreen(screen_color);

	    // Made the intro beautiful
	    drawFrame(header_background, 0, 0, 80, 4);
	    printAt("                          Q OS Text Editor                                  \r\n", header_foreground, 1, 1);
	    printAt("            A Simple Text Editor for Q OS by Raph Hennessy                    ",desc_foreground,1,2);

	    newline();
	    newline();
	    newline();
		newline();

		writing = true;
		readStr(writerContents, WRITERSIZE);
		writing = false;
	}
}
