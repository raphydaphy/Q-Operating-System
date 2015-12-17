#include "keyboard.h"
#include "strbuilder.h"
#include "list.h"

static int16 itermVal = 0;

static bool pgetkc = false, echoOn = true;
static bool shiftDown = false, capslDown = false, ctrlDown = false;

inline char retCorrespChar(char shift, char std)
{
    if(shiftDown && !capslDown)
    {
        return shift;
    }
    else if(capslDown && !shiftDown)
    {
        return isalpha(std) ? shift : std;
    }
    else if(shiftDown && capslDown)
    {
        return isalpha(std) ? std : shift;
    }
    return std;
}

static inline char __getchFromKC(int16 rch)
{
    int16 r = rch;
    switch(r) {
    case 7196: return '\n'; // <RET>
    case 3598: return '\b'; // <BKSP>
    default:
        if(r > -17990)
        {
            r /= KC_MAGIC_VAL; // Some magical increment value
            return retCorrespChar(kbShiftChars[r], kbLowerChars[r]);
        }
        else
        {
            return 0;
        }
    }
}

// stdEcho:true  - Prints char
//        :false - Prints '*'
static inline string __vreadstr(bool stdEcho)
{
    uint16 index = 0;
    strbuilder_t strb = strbuilder_init();
    int16 rch = 0;
    char ch = 0;
    while(true) {
        rch = getKeycode();
        if(echoOn)
        {
            switch(rch)
            {
            case 19424: // Left Arrow
                cursorX--;
                index--;
                continue;
            case 19936: // Right Arrow
                cursorX++;
                index++;
                continue;
            default:
                ch = __getchFromKC(rch);
                if(ch == 0)
                {
                    continue;
                }
                kprintch(stdEcho ? ch : '*', black, false);
                if(ch == '\n')
                {
                    return strbuilder_tostr(strb);
                }
                if(ch == '\b')
                {
                    // For some reason, strb.size != strb.ilist.size
                    if((cursorX == deleteStopX) && (cursorY == startCmdY))
                    {
                        continue;
                    }
                    list_remove(&(strb.ilist), --index);
                    strb.size = strb.ilist.size;
                    continue;
                }
            }
        }
        strbuilder_insertc(&strb, ch, index++);
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

int16 getKeycode()
{
    pgetkc = true;
    while(pgetkc);
    return itermVal;
}

static void kb_callback()
{
    if(inportb(0x64) & 0x1)
    {
        int16 value = inportw(0x60);
        switch(value)
        {
        case 7453:      // Ctrl Down
            ctrlDown = true;
            break;
        case -25187:    // Ctrl Up
            ctrlDown = false;
            break;
        case 10794:     // R shift down
        case 13878:     // L shift down
            shiftDown = true;
            break;
        case -21846:    // R shift up
        case -18762:    // L shift up
            shiftDown = false;
            break;
        case 14906:     // Cpslk
            capslDown = !capslDown;
            break;
        default:
            if(pgetkc)
            {
                itermVal = value;
                pgetkc = false;
            }
        }
    }
}

void initialize_keyboard()
{
    register_interrupt_handler(IRQ1, &kb_callback);
}

