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

void messageBox(string txt) {
    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

    drawBorder(header_background, 20, 12, 60, 18);
    printAt(txt, desc_foreground, 21, 13);
    printAt("[OKAY]", desc_foreground, 37, 17);

    static int releaseRET[] = {0x9C, 0};
    static int pressRET[] = {0x1C, 0};
    waitUntilKey(releaseRET);
    waitUntilKey(pressRET);

    strcpy(vidmem, oldmem);
}

int8 messageBox_YN(string txt) {
    string vidmem = (string) 0xb8000;
    char oldmem[strlen(vidmem)];
    strcpy(oldmem, vidmem);

    drawBorder(header_background, 20, 12, 60, 18);
    printAt(txt, desc_foreground, 21, 13);
    printAt("[YES]", desc_foreground, 22, 17);
    printAt("[NO]", desc_foreground, 38, 17);
    printAt("[CANCEL]", desc_foreground, 50, 17);

    static int acceptedKeys[] = {0x15 /*Y*/, 0x31 /*N*/, 0x2E /*C*/, 0}; //END WITH NULL PLZ
    int val = waitUntilKey(acceptedKeys);

    strcpy(vidmem, oldmem);
    switch(val) {
    case 0x15: return 1; // Yes == 1
    case 0x31: return -1; // No == -1
    case 0x2E: return 0; // Cancel == 0
    default: return -2; // ILLEGAL
    }
}

int waitUntilKey(int key[]) {
    while(true)
    {
        // if a key is presesd
        if(inportb(0x64) & 0x1)
        {
            uint8 value = inportb(0x60);
            for(uint16 i = 0; key[i] > 0; i++) {
                if(value == key[i])
                {
                    return key[i];
                }
            }
        }
    }
}

