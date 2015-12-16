#include "keyboard.h"

#define KB_BUFF 128

static uint8 itermVal = 0;
static bool pgetch = false;
static bool shiftDown = false, capslDown = false;

string readstr()
{
    strbuilder_t strb = strbuilder_init();
    char ch = 0;
    while(true) {
        ch = getch();
        if(ch == '\n')
        {
            return strbuilder_tostr(strb);
        }
        strbuilder_appendc(&strb, ch);
    }
}

char getch()
{
    uint8 r = 0;
    char ch = 0;
    do {
        pgetch = true;
        while(pgetch); //wait for it...
        r = itermVal;
        if(r == 0x1C)
        {
            return '\n';
        }
        if(r < 59 && r > 0)
        {
            if(shiftDown && !capslDown)
            {
                ch = kbShiftChars[r];
            }
            else if(capslDown && !shiftDown)
            {
                ch = kbCapslchars[r];
            }
            else if(shiftDown && capslDown)
            {
                ch = kbSCModchars[r];
            }
            else
            {
                ch = kbLowerChars[r];
            }
        }
    } while(ch == 0);
    return ch;
}

static void kb_callback()
{
    if(inportb(0x64) & 0x1)
    {
        uint8 value = inportb(0x60);
//        printf("0x%x", value);
        if(pgetch)
        {
            itermVal = value;
            pgetch = false;
        }
    }
}

void initialize_keyboard()
{
    register_interrupt_handler(IRQ1, &kb_callback);
}
