#include "keyboard.h"
#include "strbuilder.h"
#include "list.h"

static uint8 itermVal = 0;

static bool pgetch = false, pgetkc = false, echoOn = true;
static bool shiftDown = false, capslDown = false, ctrlDown = false;

static inline char __getch()
{
    uint8 r = 0;
    char ch = 0;
    do {
        pgetch = true;
        while(pgetch); // wait until key is pressed
        r = itermVal;
        if(r == 0x1C)
        {
            return '\n';
        }
        if(r == 0x0E)
        {
            return '\b';
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

// stdEcho:true  - Prints char
//        :false - Prints '*'
static inline string __vreadstr(bool stdEcho)
{
    strbuilder_t strb = strbuilder_init();
    char ch = 0;
    while(true) {
        ch = __getch();
        if(echoOn)
        {
            kprintch(stdEcho ? ch : '*', black, false);
            if(ch == '\n')
            {
                return strbuilder_tostr(strb);
            }
            if(ch == '\b')
            {
                // For some reason, strb.size != strb.ilist.size
                strbuilder_rmchar(&strb, strb.ilist.size - 1);
                continue;
            }
        }
        strbuilder_appendc(&strb, ch);
    }
}

string readstr()
{
    return __vreadstr(true);
}

string readpasswd()
{
    return __vreadstr(false);
}

char getch()
{
    return readstr()[0];
}

uint8 getKeycode()
{
    pgetkc = true;
    while(pgetkc);
    return itermVal;
}

static void kb_callback()
{
    if(inportb(0x64) & 0x1)
    {
        uint8 value = inportb(0x60);
//        printf("0x%x", value);
        if(pgetkc)
        {
            itermVal = value;
            pgetkc = false;
        }
        else
        {
            switch(value)
            {
            case 0x1D:
                ctrlDown = true;
                break;
            case 0x9D:
                ctrlDown = false;
                break;
            case 0x2A:
            case 0x36:
                shiftDown = true;
                break;
            case 0xAA:
            case 0xB6:
                shiftDown = false;
                break;
            case 0x3A:
                capslDown = !capslDown;
                break;
            default:
                if(pgetch)
                {
                    itermVal = value;
                    pgetch = false;
                }
                break;
            }
        }
    }
}

void initialize_keyboard()
{
    register_interrupt_handler(IRQ1, &kb_callback);
}
