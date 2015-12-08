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

