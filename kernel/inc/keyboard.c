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

static inline void __simEndKey(strbuilder_t strb, uint16 *index)
{
    while(true)
    {
        if(strbuilder_charAt(strb, *index) == 0)
        {
            break;
        }
        else
        {
            if(cursorX + 1 == sw)
            {
                cursorY++;
                cursorX = 0;
            }
            else
            {
                cursorX++;
            }
            (*index)++;
        }
    }
    updateCursor();
}

static inline void __simHeadKey(uint16 *index)
{
    while(true)
    {
        if((cursorY == startCmdY) && (cursorX <= deleteStopX))
        {
            break;
        }
        else
        {
            if(cursorX - 1 == 0)
            {
                cursorY--;
                cursorX = sw;
            }
            else
            {
                cursorX--;
            }
            (*index)--;
        }
    }
    updateCursor();
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

static inline void __simLeftArrow(uint16 *index)
{
    cursorX--;
    (*index)--;
    updateCursor();
}

static inline void __simRightArrow(uint16 *index)
{
    cursorX++;
    (*index)++;
    updateCursor();
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
//            printAt(itos10(rch), white, 0, 0);
            switch(rch)
            {
            case 19424: // Left Arrow
                __simLeftArrow(&index);
                continue;
            case 19936: // Right Arrow
                __simRightArrow(&index);
                continue;
            case 18656: // Up Arrow
            case 20704: // Down Arrow
                continue;
            case 23520: // Windows Key!!!
                ch = 0x01;
                kprintch(stdEcho ? ch : '*', black, false);
                break;
            case 18400: // Home Key
                __simHeadKey(&index);
                continue;
            case 20448: // End Key
                __simEndKey(strb, &index);
                continue;
            default:
                if(rch < 0) // This should intercept the release codes
                {
                    continue;
                }
                ch = __getchFromKC(rch);
                if(ch == 0)
                {
                    continue;
                }
                if(ctrlDown)
                {
                    char ctrlCh = toLowerC(ch);
                    switch(ctrlCh)
                    {
                    case 'a': // Ctrl-a is head
                        __simHeadKey(&index);
                        continue;
                    case 'e': // Ctrl-a is head
                        __simEndKey(strb, &index);
                        continue;
                    case 'b':
                        __simLeftArrow(&index);
                        continue;
                    case 'f':
                        __simRightArrow(&index);
                        continue;
                    }
                }
                if((ch == '\b') && (cursorY == startCmdY) && (cursorX <= deleteStopX))
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
                    list_remove(&(strb.ilist), --index);
                    strb.size = strb.ilist.size;
                    continue;
                }
            }
        }
        strbuilder_insertc(&strb, ch, index++);
    }
}

inline string readstr()
{
    return __vreadstr(true);
}

inline string readpasswd()
{
    return __vreadstr(false);
}

inline char getch()
{
    return readstr()[0];
}

inline int16 getKeycode()
{
    pgetkc = true;
    while(pgetkc);
    return itermVal;
}

static void kb_callback()
{
    if(inportb(0x64) & 0x1)
    {
        int16 value = IoRead16(0x60);
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
