//This file has most of the C functions for Q OS at the moment
//I will be moving functions into seperate files later [eta:2 months]

#ifndef SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"
//Variables for the kernel functions
uint8 writing = 0;
uint8 progexit = 0;
uint8 layout = 0;
uint8 ctrl = 0;
string writerContents = "Welcome to the Writer program. Start typing to modify this file. Anything you type will override the current contents of the file.";

//Variables for screen.h functions
int cursorX = 0, cursorY = 0;
const uint8 sw = 80,sh = 25,sd = 2;                                                     //define the screen width, height, and depth.
void clearLine(uint8 from,uint8 to)
{
        uint16 i = sw * from * sd;
        string vidmem=(string)0xb8000;
        for(i;i<(sw*to*sd);i++)
        {
                vidmem[i] = 0x0;
        }
}
void updateCursor()
{
    unsigned temp;

    temp = cursorY * sw + cursorX;                                                      // Position = (y * width) +  x

    outportb(0x3D4, 14);                                                                // CRT Control Register to Select Cursor Location
    outportb(0x3D5, temp >> 8);                                                         // ASM to send the high byte across the bus
    outportb(0x3D4, 15);                                                                // Another CRT Control Register to Select Send Low byte
    outportb(0x3D5, temp);                                                              // Use ASM outportb function again to send the Low byte of the cursor location
}
void clearScreen()
{
        clearLine(0,sh-1);
        cursorX = 0;
        cursorY = 0;
        updateCursor();
}

void scrollUp(uint8 lineNumber)
{
        string vidmem = (string)0xb8000;
        uint16 i = 0;
        clearLine(0,lineNumber-1);                                        
        for (i;i<sw*(sh-1)*2;i++)
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
        if(cursorY >=sh-1)
        {
                scrollUp(1);
        }
}

void printch(char c,int b)
{
    string vidmem = (string) 0xb8000;     
    switch(c)
    {
        case (0x08):
                if(cursorX > 0) 
                {
	                cursorX--;									
                        vidmem[(cursorY * sw + cursorX)*sd]=0x00;	                              
	        }
	        break;
       /* case (0x09):
                cursorX = (cursorX + 8) & ~(8 - 1); 
                break;*/
        case ('\r'):
                cursorX = 0;
                break;
        case ('\n'):
                cursorX = 0;
                cursorY++;
                break;
        default:
                vidmem [((cursorY * sw + cursorX))*sd] = c;
                vidmem [((cursorY * sw + cursorX))*sd+1] = b;
                cursorX++; 
                break;
	
    }
    if(cursorX >= sw)                                                                   
    {
        cursorX = 0;                                                                
        cursorY++;                                                                    
    }
    updateCursor();
    newLineCheck();
}

void print (string ch,int bh)
{
        uint16 i = 0;
        uint8 length = strlength(ch)-1;              
        for(i;i<length;i++)
        {
                printch(ch[i],bh);
        }
}

#endif

