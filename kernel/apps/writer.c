#include "writer.h"

#include "../inc/intTypeDefs.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"

#ifndef WRITERSIZE
#define WRITERSIZE 1024
#endif

void writer()
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

void writerHelp()
{
	newline();
	print("Showing help for writer:",0x0F);
	newline();
	print("[HELP SECTION HERE]",0x0F);
}
