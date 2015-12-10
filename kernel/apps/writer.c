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

void writeFile(fs_node_t* fsnode)
{
    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        const uint32 fsSize = fsnode->length;
        char buffer[fsSize];
		const uint32 offset = 0;
        buffer[0] = 1;
        buffer[1] = 3;

		print("\nWrite Operation Returned Value: ",bright_red);
        printint(write_fs(fsnode, offset, fsSize, (uint8*) buffer),red);

		print("\n\nWrite Operation Modified Data: \n",bright_red);
		for(uint8 counter = offset;counter<fsSize;counter++)
		{
			printch(buffer[counter],yellow);
		}
    }
    newline();
    print("\nNew File: ",green);
    catTheFile(fsnode);
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
