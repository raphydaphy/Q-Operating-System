//make sure that we don't duplicate the code
#ifndef SCREENUTILS_H
#define SCREENUTILS_H

//include dependent files for screen.c
#include "assemblyFunctions.h"
#include "stringUtils.h"

//define variables for kernel.c
bool writing; 
bool progexit; 
bool alt;
bool ctrl;
bool lshift;
bool rshift;
bool capslock;
bool typingCmd; 
uint8 startCmdY; 
uint8 startCmdX; 
bool newCmd;

//define variables for screen.c
uint32 cursorX, cursorY, deleteStopX; // Since cursors cannot be negative
const uint8 sw, sh, sd;

//define functions for screen.c
void clearLine(uint8, uint8);
void updateCursor();
void clearScreen();
void scrollUp(uint8);
void newLineCheck();
void printch(char, int);
void print(string, int);
void printint(int, int);
void printfloat(float, int);
void printhex(uint32, int);
void moveCursorX(int);
void moveCursorY(int);
/* Only call kprintch in kernels */
void kprintch(char, int, bool);
/* Macros */
#define newline() \
    printch('\n', 0x0F);
#define println(str, c) \
    print(str, c); \
    newline();

//end the if statment at the start of the file
#endif
