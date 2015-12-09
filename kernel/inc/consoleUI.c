#include "consoleUI.h"

void paintScreen(int color) {
    for(uint16 i = 0; i < (sw * 25 * sd); i += 2)
    {
        printch(' ', color);
    }
    cursorX = 0;
    cursorY = 0;
    updateCursor();
}

static inline void __appendCharAt(char c, int b, uint16 x, uint16 y) {
    string vidmem = (string) 0xb8000;
    vidmem [(y * sw + x) * sd] = c;
    vidmem [(y * sw + x) * sd + 1] = b;
}

void printAt(string str, int color, uint16 x, uint16 y) {
    const uint8 length = strlen(str);
    const uint16 oldX = x; // This cannot be changed
    for(uint16 i = 0; i < length; i++)
    {
        switch(str[i]) {
        case '\r':
            x = oldX;
            break;
        case '\n':
            y++;
            break;
        case '\b':
            __appendCharAt(' ', color, --x, y);
            break;
        default:
            __appendCharAt(str[i], color, x++, y);
            break;
        }
    }
}
