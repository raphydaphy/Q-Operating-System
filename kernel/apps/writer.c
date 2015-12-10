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
	else if (streql(splitArg(args, 1)))
	{

	}
	    paintScreen(screen_color);

	    drawFrame(header_background, 0, 0, 80, 4);
		printAt("Q OS Text Editor\r\n", header_foreground, 1, 1);
	    printAt("Simple, Single Document Text Editor built for Q OS by Raph Hennessy",desc_foreground,1,2);

		drawBorder(screen_background, 0, 4, 80, sh - 1);

		cursorY = 5;
		cursorX = 1;
		updateCursor();

		writing = true;
		printAt(writerContents,white,1,5);
		readStr(writerContents, WRITERSIZE);
		writing = false;
	}
}
