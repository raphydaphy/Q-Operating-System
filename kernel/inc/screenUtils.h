//make sure that we don't duplicate the code
#ifndef SCREENUTILS_H
#define SCREENUTILS_H

//include dependent files for screen.c
#include "assemblyFunctions.h"
#include "stringUtils.h"
#include "consoleUI.h"

// the screen color in 0xXX and 0xX form with the X being replaced by color in hex notation
#define screen_color 0x99

// the first line of text and background color of all main app headers (such as writer.c)
#define header_background 0x38
#define header_foreground 0x39

// the color of the second line of text in all main app headers (such as printIntro)
#define desc_foreground 0x34

// all the colors that can be used in a print statement using default background color
typedef enum {
    black = 0x90,
    blue = 0x91,
    light_green = 0x92,
    grey = 0x93,
    red = 0x94,
    purple = 0x95,
    brown = 0x96,
    light_grey = 0x97,
    dark_grey = 0x98,
    light_blue = 0x99,
    green = 0x9A,
    cyan = 0x9B,
    bright_red = 0x9C,
    magenta = 0x9D,
    yellow = 0x9E,
    white = 0x9F
} colors;

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
void clearLine(uint8, uint8, int);
void updateCursor();
void clearScreen();
void scrollUp(uint8);
void newLineCheck();
void printch(char, int);
void print(string, int);

#define printint(n, bh) \
    print(itos10(n), bh)

#define printfloat(n, bh) \
    print(ftos(n), bh)

#define printhex(n, bh) \
    print("0x", bh); \
    print(itos16(n), bh)

void moveCursorX(int);
void moveCursorY(int);
/* Only call kprintch in kernels */
void kprintch(char, int, bool);
/* Macros */
#define newline() \
    printch('\n', white)

#define println(str, c) \
    print(str, c); \
    newline()

//end the if statment at the start of the file
#endif
