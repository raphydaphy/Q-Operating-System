//make sure that we don't duplicate the code
#ifndef SCREEN_H
#define SCREEN_H

//include dependent files for screen.c
#include "system.h"
#include "string.h"

//define variables for kernel.c
uint8 writing; 
uint8 progexit; 
uint8 layout; 
uint8 ctrl; 
uint8 typingCmd; 
uint8 startCmdY; 
uint8 startCmdX; 
uint8 newCmd;
string writerContents;

//define variables for screen.c
int cursorX, cursorY;
const uint8 sw, sh, sd;

//define functions for screen.c
void clearLine(uint8 from,uint8 to);
void updateCursor();
void clearScreen();
void scrollUp(uint8 lineNumber);
void newLineCheck();
void printch(char c,int b);
void print (string ch,int bh);

//end the if statment at the start of the file
#endif
