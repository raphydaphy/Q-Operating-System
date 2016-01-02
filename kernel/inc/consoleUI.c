#include "consoleUI.h"
#include "kheap.h" // Do not move this line in the .h file

void paintScreen(int color) {
    string vidmem = (string) 0xb8000;
    for(uint16 i = 0; i < (sw * 25 * sd); i++)
    {
        vidmem [i] = ' ';
        vidmem [++i] = color;
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

void printCharAt(char ch, int color, uint16 x, uint16 y) {
    switch(ch) {
    case '\r':
    case '\n':
        break; // Pointless chars
    case '\b':
        __appendCharAt(' ', color, --x, y);
        break;
    default:
        __appendCharAt(ch, color, x, y);
        break;
    }
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

void drawFrame(int color, uint16 x, uint16 y, uint16 xlen, uint16 ylen) {
    const uint16 oldY = y;
    const uint16 oldX = x;
    for( ; y < ylen; y++) {
        for(x = oldX; x < xlen; x++) {
            if (y == oldY) {
                if(x == oldX) {
                    __appendCharAt((char) T_L_S, color, x, y);
                } else if (x == xlen - 1) {
                    __appendCharAt((char) T_R_S, color, x, y);
                } else {
                    __appendCharAt((char) H_S, color, x, y);
                }
            } else if (y == ylen - 1) {
                if(x == oldX) {
                    __appendCharAt((char) B_L_S, color, x, y);
                } else if (x == xlen - 1) {
                    __appendCharAt((char) B_R_S, color, x, y);
                } else {
                    __appendCharAt((char) H_S, color, x, y);
                }
            } else {
                if(x > oldX && x < xlen - 1) {
                    __appendCharAt(' ', color, x, y);
                } else {
                    __appendCharAt((char) V_S, color, x, y);
                }
            }
        }
    }
    cursorX = 0;
    cursorY = 0;
    updateCursor();
}

void drawBorder(int color, uint16 x, uint16 y, uint16 xlen, uint16 ylen) {
    const uint16 oldY = y;
    const uint16 oldX = x;
    for( ; y < ylen; y++) {
        for(x = oldX; x < xlen; x++) {
            if (y == oldY) {
                if(x == oldX) {
                    __appendCharAt((char) T_L_D, color, x, y);
                } else if (x == xlen - 1) {
                    __appendCharAt((char) T_R_D, color, x, y);
                } else {
                    __appendCharAt((char) H_D, color, x, y);
                }
            } else if (y == ylen - 1) {
                if(x == oldX) {
                    __appendCharAt((char) B_L_D, color, x, y);
                } else if (x == xlen - 1) {
                    __appendCharAt((char) B_R_D, color, x, y);
                } else {
                    __appendCharAt((char) H_D, color, x, y);
                }
            } else {
                if(x > oldX && x < xlen - 1) {
                    __appendCharAt(' ', color, x, y);
                } else {
                    __appendCharAt((char) V_D, color, x, y);
                }
            }
        }
    }
    cursorX = 0;
    cursorY = 0;
    updateCursor();
}

void paintLine(int color, uint16 x, uint16 y, uint16 xlen) {
    for( ; x < xlen; x++) {
        __appendCharAt(' ', color, x, y);
    }
}

void messageBox(string txt, ...) {
    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

    va_list ap;
    va_start(ap, txt);
    string onscreenTxt = __vstrformat(txt, ap);
    va_end(ap);

    drawBorder(header_background, 20, 12, 60, 18);
    printAt(onscreenTxt, desc_foreground, 21, 13);
    printAt("[OKAY]", desc_foreground, 37, 17);

    waitUntilKey(1, 0x9C);
    waitUntilKey(1, 0x1C);

    strcpy(vidmem, oldmem);
}

int8 messageBox_YN(string txt, ...) {
    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

    va_list ap;
    va_start(ap, txt);
    string onscreenTxt = __vstrformat(txt, ap);
    va_end(ap);

    drawBorder(header_background, 20, 12, 60, 18);
    printAt(onscreenTxt, desc_foreground, 21, 13);
    printAt("[YES]", desc_foreground, 22, 17);
    printAt("[NO]", desc_foreground, 38, 17);
    printAt("[CANCEL]", desc_foreground, 50, 17);

    int val = waitUntilKey(3, 0x15 /*Y*/, 0x31 /*N*/, 0x2E /*C*/);

    strcpy(vidmem, oldmem);
    switch(val) {
    case 0x15: return 1; // Yes == 1
    case 0x31: return -1; // No == -1
    case 0x2E: return 0; // Cancel == 0
    default: return -2; // ILLEGAL
    }
}

static inline string __vMessageBoxIn(string txt, bool isPasswd) {
    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

    drawBorder(header_background, 20, 12, 60, 18);
    printAt(txt, desc_foreground, 21, 13);
    paintLine(white, 21, 16, 59);

    cursorX = deleteStopX = 21;
    cursorY = startCmdY = 16;
    int strLen = 59 - 21;
    string inputBuf = (string) kmalloc(strLen * sizeof(char));
    readStr(inputBuf, strLen, isPasswd);

    strcpy(vidmem, oldmem);
    return inputBuf;
}

string messageBox_I(string txt, ...) {
    va_list ap;
    va_start(ap, txt);
    string onscreenTxt = __vstrformat(txt, ap);
    va_end(ap);
    return __vMessageBoxIn(onscreenTxt, false);
}


string messageBox_Pass(string txt, ...) {
    va_list ap;
    va_start(ap, txt);
    string onscreenTxt = __vstrformat(txt, ap);
    va_end(ap);
    return __vMessageBoxIn(onscreenTxt, true);
}

int waitUntilKey(const int count, ...) {
    va_list ap;
    int kIndex, ckey;
    uint8 value;
    va_start(ap, count);
    while(true)
    {
        // if a key is presesd
        if(inportb(0x64) & 0x1)
        {
            value = inportb(0x60);
            for(kIndex = 0; kIndex < count; kIndex++) {
                ckey = va_arg(ap, int);
                if(value == ckey)
                {
                    va_end(ap);
                    return ckey;
                }
            }
            va_end(ap);
            va_start(ap, count); // Redo...
        }
    }
}

// Watch out... getkey waits until the key is released
int getKey() {
    while(true)
    {
        // if a key is presesd
        uint8 value = getAnyKey();
        if(value < 59) {
            return value;
        }
    }
}

int getAnyKey() {
    while(true)
    {
        // if a key is presesd
        if(inportb(0x64) & 0x1)
        {
            return inportb(0x60);
        }
    }
}
