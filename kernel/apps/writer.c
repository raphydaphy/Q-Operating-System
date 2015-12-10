#include "writer.h"

void writerHelp()
{
	newline();
	print("Showing help for writer:",magenta);
	newline();
	print("Writer is a simple text editor built into Q OS that saves a single document at a time.\nAfter the first lnie of text saved your document may be presented in a strange format.",yellow);
}

void writer(string args)
{
	if (streql(splitArg(args, 1),"-h"))
	{
		writerHelp();
	}
	else if (streql(splitArg(args, 1),"new"))
	{
		paintScreen(screen_color);

	    drawFrame(header_background, 0, 0, 80, 4);
		printAt("Q OS Text Editor\r\n", header_foreground, 1, 1);
	    printAt("Simple, Single Document Text Editor built for Q OS by Raph Hennessy",desc_foreground,1,2);

		drawBorder(screen_background, 0, 4, 80, sh - 1);

		cursorY = 5;
		cursorX = 1;
		updateCursor();

		writing = true;
		readStr(writerContents, WRITERSIZE);
		writing = false;
	}
	else
	{
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
