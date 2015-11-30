//include the code from the respective header file
#include "screenUtils.h"

//Initialize the variables created in screen.h
bool writing = 0, progexit = 0, layout = 0, ctrl = 0, typingCmd = 0;
uint8 startCmdY = 0, startCmdX = 0;
bool newCmd = 0;

//Setup variables needed for this file
uint32 cursorX = 0, cursorY = 0, deleteStopX = 0;
const uint8 sw = 80,sh = 26,sd = 2;

void clearLine(uint8 from, uint8 to)
{
    string vidmem=(string)0xb8000;
    for(uint16 i = sw * from * sd; i < (sw * to * sd); i++)
    {
        vidmem[i] = 0x0;
    }
}

void updateCursor()
{
    unsigned temp;

    temp = cursorY * sw + cursorX;                                              // Position = (y * width) +  x

    outportb(0x3D4, 14);                                                        // CRT Control Register to Select Cursor Location
    outportb(0x3D5, temp >> 8);                                                 // ASM to send the high byte across the bus
    outportb(0x3D4, 15);                                                        // Another CRT Control Register to Select Send Low byte
    outportb(0x3D5, temp);                                                      // Use ASM outportb function again to send the Low byte of the cursor location
}

void clearScreen()
{
    clearLine(0, sh - 1);
    cursorX = 0;
    cursorY = 0;
    updateCursor();
}

void scrollUp(uint8 lineNumber)
{
    string vidmem = (string) 0xb8000;
    clearLine(0, lineNumber - 1);
    for (uint16 i = 0; i<sw * (sh - 1) * 2; i++)
    {
        vidmem[i] = vidmem[i+sw*2*lineNumber];
    }
    clearLine(sh-1-lineNumber,sh-1);
    if((cursorY - lineNumber) < 0 ) 
    {
        cursorY = 0;
        cursorX = 0;
    } 
    else 
    {
        cursorY -= lineNumber;
    }
    updateCursor();
}


void newLineCheck()
{
    if(cursorY >= sh - 1)
    {
        scrollUp(1);
    }
}

void kprintch(char c, int b, bool incDelStop)
{
    string vidmem = (string) 0xb8000;     
    switch(c)
    {
    case (0x08): // Backspace
        if(cursorX > 0) 
        {
            cursorX--;
            if (incDelStop) deleteStopX--;
            vidmem[(cursorY * sw + cursorX)*sd] = 0x00;
        }
        break;
    case ('\t'): {
        int modX = cursorX % 4; // Tabs are 4 spaces wide
        modX = modX == 0 ? 4 : modX;
        while(modX--) {
            printch(' ', b);
        }
        break;
    }
    case ('\r'):
        cursorX = 0;
        if (incDelStop) deleteStopX = 0;
        break;
    case ('\n'):
        cursorX = 0;
        if (incDelStop) deleteStopX = 0;
        cursorY++;
        break;
    default:
        vidmem [((cursorY * sw + cursorX))*sd] = c;
        vidmem [((cursorY * sw + cursorX))*sd+1] = b;
        cursorX++;
        if (incDelStop) deleteStopX++;
        break;
    }
    if(cursorX >= sw)
    {
        cursorX = 0;
        if (incDelStop) deleteStopX = 0;
        cursorY++;
    }
    updateCursor();
    newLineCheck();
}

void printch(char c, int b)
{
    kprintch(c, b, true);
    startCmdY = cursorY;
}

void print(string ch, int bh)
{
    uint8 length = strlength(ch);
    for(uint16 i = 0; i < length; i++)
    {
        printch(ch[i], bh);
    }
}

void moveCursorX(int x) {
    cursorX += x;
    while(cursorX < 0) {
        cursorX += sw;
        cursorY -= 1;
    }
    while(cursorX >= sw) {
        cursorX -= sw;
        cursorY += 1;
    }
    updateCursor();
    newLineCheck();
}

void moveCursorY(int y) {
    cursorY += y;
    updateCursor();
    newLineCheck();
}
