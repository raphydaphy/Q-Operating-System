#include "writer.h"

void writerHelp()
{
	newline();
	print("Showing help for writer:",magenta);
	newline();
	print("Writer is a simple text editor built into Q OS\n",yellow);
	print("Your text will probably be saved when you exit with Control + Z\n",yellow);
	print("To start a new document simply type 'writer new'\n",yellow);
	print("To access your last document type 'writer' with no arguments.\n",yellow);
	print("After the first line of text saved your document may be shown unformatted.",yellow);
}

void initWriter()
{
	paintScreen(screen_color);

	drawFrame(header_background, 0, 0, 80, 4);
	printAt("Q OS Text Editor\r\n", header_foreground, 1, 1);
	printAt("Simple, Single Document Text Editor built for Q OS by Raph Hennessy",desc_foreground,1,2);

	drawBorder(screen_background, 0, 4, 80, sh - 1);

	cursorY = 5;
	cursorX = 1;
	updateCursor();
}
void writer(string args)
{
	if (streql(splitArg(args, 1),"-h"))
	{
		writerHelp();
	}
	else if (streql(splitArg(args, 1),"new"))
	{
		initWriter();

		writing = true;
		readStr(writerContents, WRITERSIZE,false);
		writing = false;
	}
	else
	{
	    initWriter();

		writing = true;
		printAt(writerContents,white,1,5);
		readStr(writerContents, WRITERSIZE,false);
		writing = false;
	}
}
