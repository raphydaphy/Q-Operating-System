#include "kbDetect.h"

bool buffOverflow = false;

const int BUFSIZE = 256;
const char chars[256] =    {
     0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=',  0 ,'\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0 ,  0 ,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
   '\'', '`',  0 ,'\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,
};
const char charsShift[256] =    {
     0 ,  0 , '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+',  0 ,'\t', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',  0 ,  0 ,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
   '\"', '~',  0 , '|', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?',  0 , '*',  0 , ' ',  0 ,
};
const char charsCapsLock[256] =    {
     0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=',  0 ,'\t', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',  0 ,  0 ,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
   '\'', '`',  0 ,'\\', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,
};

uint8 backspaceOne(uint8 i, string buffstr, uint32 bufSize) {
    kprintch('\b', 0x0F, false);
    i--;
    char old = buffstr[i];
    if(old == '\t') {
        int delCount = i % 4;
        delCount = delCount == 0? 4 : delCount;
        while(delCount--) {
            buffstr[i] = 0;
            kprintch('\b', 0x0F, false);
            i--;
        }
        i++;
    } else buffstr[i] = 0;
    if(i < bufSize) {
        buffOverflow = false;
    }
    return i;
}

uint8 backspaceMul(uint8 i, string buffstr, uint32 bufSize) {
    char old; // This is a place holder
    do {
        kprintch('\b', 0x0F, false);
        i--;
        old = buffstr[i];
        buffstr[i] = 0;
    } while ((old >= 97 && old <= 122) || (old >= 65 && old <= 90));
    if(i < bufSize) {
        buffOverflow = false;
    }
    return i;
}

uint8 pushCtrlChar(uint8 i, string buffstr, char caps, uint32 bufSize) {
    kprintch('^', 0x0F, false);
    buffstr[i] = '^';
    i++;
    kprintch(caps, 0x0F, false);
    buffstr[i] = caps;
    if(++i >= bufSize) {
        buffOverflow = true;
    }
    return i;
}

uint32 charKeyPressed(string buffstr, uint8 ch, uint32 i, uint32 bufSize) {
    int toPrint = 0xFF;
    bool shiftMask = lshift || rshift;
    /* Shift and Caps on should be lowercase */
    if(shiftMask && !capslock) {
        toPrint = charsShift[ch];
    } else if(capslock && !shiftMask) {
        toPrint = charsCapsLock[ch];
    } else {
        toPrint = chars[ch];
    }
    if(ctrl) {
        /* Ctrl key pushes an Uppercase */
        return pushCtrlChar(i, buffstr, charsCapsLock[ch], bufSize);
    } else if (alt) {
        /* Alt key pushes a lowercase */
        return pushCtrlChar(i, buffstr, chars[ch], bufSize);
    }
    buffstr[i] = toPrint;
    kprintch(toPrint, 0x0F, false);
    if(++i >= bufSize) {
        buffOverflow = true;
    }
    return i;
}

void moveDown()
{
    cursorY = cursorY + 1;
    cursorX = cursorX - 1;
    updateCursor();
}

void moveUp()
{
    cursorY = cursorY - 1;
    cursorX = cursorX - 1;
    updateCursor();
}

void readStr(string buffstr, uint32 bufSize)
{
    uint32 i = 0;
    bool reading = true;
    while(reading)
    {
    	//exit the writer program when the Ctrl-Z key is pressed
	    if (progexit && writing)
	    {
	        clearScreen();
	        updateCursor();
	        writing = false;
	        progexit = false;
	        print("Q-Kernel>  ", 0x08);
	    }


	    if (newCmd && typingCmd)
	    {
	        startCmdX = cursorX;
	        startCmdY = cursorY;
	        newCmd = 0;
	    }

	    //Detect keypress and return string of characters pressed to the buffstr char array
        if(inportb(0x64) & 0x1)
        {
            uint8 value = inportb(0x60);
            if (deleteStopX > 0) {
	            if ((cursorX == deleteStopX) && (cursorY == startCmdY)) {
                    /* Make sure user cannot press delete anymore */
	                if (value == 14)
                        continue;
	            }
            }
            /* Make sure the user can only press delete */
            if (buffOverflow) {
                if (value == 14)
                    buffOverflow = false;
                else
                    continue;
            }
            bool handled = false;
            switch(value)
            {
            case 29:        // Left Ctrl Down
                ctrl = true;   // Toggle On
                break;
            case 157:       // Left Ctrl Up
                ctrl = false;   // Toggle Off
                break;
            case 1:         // Esc (Ctrl-z)
                if (writing) {
                    progexit = true;
                    reading = false;
                } else {
                    i = pushCtrlChar(i, buffstr, 'Z', bufSize);
                }
                break;
            case 14:                // Backspace
                if (lshift || rshift) { // On of the shifts are activated
                    // Delete until space | non-word | different-cased-word
                    i = backspaceMul(i, buffstr, bufSize);
                } else {
                    // No shift -> delete one char
                    i = backspaceOne(i, buffstr, bufSize);
                }
                break;
            case 25:
                if (ctrl) {
                    if (writing) {
                        moveUp();
                        handled = true;
                    }
                }
                break;
            case 28:				//This is the enter key, we need to add more functionality to it with Writer and other commands
                if (writing)
                {
                    printch('\n',0x0F);
                    buffstr[i] = '\n';
                    i++;
                }
                else
                {
                    reading = false;
                }
                break;
            case 30:
                if (ctrl) {
                    moveCursorX(-cursorX + deleteStopX);
                    handled = true;
                }
                break;
            case 38:
                if (ctrl) {
                    /* Make sure no clear screen during writer session */
                    if (!writing) {
                        clearScreen();
                        // Returns command "skip" which does nothing
                        strcpy(buffstr, "skip");
                        buffstr[4] = '\0'; /* Set EOL */
                        handled = true;
                        return;
                    }
                }
                break;
            case 42:        //Left shift
                lshift = true;
                break;
            case 44:        // z or Ctrl-Z
                if (ctrl) {
                    if (writing) {
                        progexit = true;
                        reading = false;
                        handled = true;
                    }
                }
                break;
            case 48:
                if (ctrl) {
                    moveCursorX(-1);
                    handled = true;
                }
                break;
            case 49:
                if (ctrl) {
                    if (writing) {
                        moveDown();
                        handled = true;
                    }
                }
                break;
            case 54:            // Right shift on
                rshift = true;     // Toggle On
                break;
            case 56:            // Left/Right alt On
                alt = true;        // Toggle On
                break;
            case 58:            // Capslock down
                capslock = !capslock;
                break;
            case 72:                //Up arrow
                if (writing) {
                    moveUp();
                }
                break;
            case 75:				//Left Arrow
                moveCursorX(-1);
                break;
            case 77:				//Right Arrow
                moveCursorX(1);
                break;
            case 80:				//Down Arrow
                if (writing) {
                    moveDown();
                }
                break;
            case 170:           // Left shift released (http://wiki.osdev.org/PS2_Keyboard)
                lshift = false;
                break;
            case 182:           // Right shift released (http://wiki.osdev.org/PS2_Keyboard)
                rshift = false;     // Toggle Off
                break;
            case 184:           // Left/Right alt Off
                alt = false;        // Toggle Off
                break;
            }
            if(!handled && chars[value]) {
                i = charKeyPressed(buffstr, value, i, bufSize);
            }
        }
    }
    buffstr[i] = 0;
}

void kbHelp()
{
    print("\nKeybindings in Q OS:", 0x0F);
    print("\n\tCtrl-b -> left", 0x0F);
    print("\n\tCtrl-f -> right", 0x0F);
    print("\n\tCtrl-a -> home", 0x0F);
    print("\n\tCtrl-p -> up", 0x0F);
    print("\n\tCtrl-n -> down", 0x0F);
    print("\n\tCtrl-z -> quit", 0x0F);
    println("\n\tCtrl-l -> clear", 0x0F);
}
