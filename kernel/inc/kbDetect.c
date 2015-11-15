#include "kbDetect.h"

uint8 pushShiftChar(uint8 i, string buffstr, char noShift, char withShift) {
    char inc = noShift;
    uint8 shiftMask = lshift | rshift;
    if (noShift >= 97 && noShift <= 122) { // Range that capslock work: [a-z]
        if (shiftMask ^ capslock == 1) {
            inc = withShift;
        }
    } else {
        if (shiftMask == 1) { // Check shifts only
            inc = withShift;
        }
    }
    printch(inc, 0x0F);
    buffstr[i] = inc;
    return ++i;
}

uint8 backspaceOne(uint8 i, string buffstr) {
    printch('\b', 0x0F);
    i--; 
    buffstr[i] = 0;
    return i;
}

uint8 backspaceMul(uint8 i, string buffstr) {
    char old = ' '; // This is a place holder
    do {
        printch('\b', 0x0F);
        i--;
        old = buffstr[i];
        buffstr[i] = 0;
    } while ((old >= 97 && old <= 122) || (old >= 65 && old <= 90));
    return i;
}

uint8 pushCtrlChar(uint8 i, string buffstr, char caps) {
    printch('^', 0x0F);
    buffstr[i] = '^';
    i++;
    printch(caps, 0x0F);
    buffstr[i] = caps;
    return ++i;
}

string readStr()
{
    char buff;
    string buffstr;
    uint8 i = 0;
    uint8 reading = 1;
    while(reading)
    {
        //print(buffstr,0x0F);
    	//exit the writer program when the Ctrl-Z key is pressed
	    if (progexit == 1 && writing == 1)
	    {
	        clearScreen();
	        updateCursor();
	        writing = 0;
	        progexit = 0;
	        print("Q-Kernel>  ", 0x08);
	    }

	    if (typingCmd)
	    {
	        if (cursorX < 11 && cursorY == startCmdY)
	        {
	            cursorX = 11;
	        }
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
            switch(inportb(0x60))
            { 
            case 29:        // Left Ctrl Down
		        ctrl = 1;   // Toggle On
                break;
            case 157:       // Left Ctrl Up
                ctrl = 0;   // Toggle Off
                break;
            case 1:         // Esc (Ctrl-z)
                if (writing == 1) {
    	            progexit = 1;
		            reading = 0;
	                //writing = 0;
	            } else i = pushCtrlChar(i, buffstr, 'Z');
                break;
            case 2:
                i = pushShiftChar(i, buffstr, '1', '!');
                break;
            case 3:
                i = pushShiftChar(i, buffstr, '2', '@');
                break;
            case 4:
                i = pushShiftChar(i, buffstr, '3', '#');
                break;
            case 5:
                i = pushShiftChar(i, buffstr, '4', '$');
                break;
            case 6:
                i = pushShiftChar(i, buffstr, '5', '%');
                break;
            case 7:
                i = pushShiftChar(i, buffstr, '6', '^');
                break;
            case 8:
                i = pushShiftChar(i, buffstr, '7', '&');
                break;
            case 9:
                i = pushShiftChar(i, buffstr, '8', '*');
                break;
            case 10:
                i = pushShiftChar(i, buffstr, '9', '(');
                break;
            case 11:
                i = pushShiftChar(i, buffstr, '0', ')');
                break;
            case 12:
                i = pushShiftChar(i, buffstr, '-', '_');
                break;
            case 13:
                i = pushShiftChar(i, buffstr, '=', '+');
                break;
            case 14:                // Backspace
                if (lshift | rshift == 1) { // On of the shifts are activated
                    // Delete until space | non-word | different-cased-word
                    i = backspaceMul(i, buffstr);
                } else {
                    // No shift -> delete one char
                    i = backspaceOne(i, buffstr);
                }
                break;
            case 15:
                i = pushShiftChar(i, buffstr, '\t', '\t');
                break;
            case 16:
                i = pushShiftChar(i, buffstr, 'q', 'Q');
                break;
            case 17:
                i = pushShiftChar(i, buffstr, 'w', 'W');
                break;
            case 18:
                i = pushShiftChar(i, buffstr, 'e', 'E');
                break;
            case 19:
                i = pushShiftChar(i, buffstr, 'r', 'R');
                break;
            case 20:
                i = pushShiftChar(i, buffstr, 't', 'T');
                break;
            case 21:
                i = pushShiftChar(i, buffstr, 'y', 'Y');
                break;
            case 22:
                i = pushShiftChar(i, buffstr, 'u', 'U');
                break;
            case 23:
                i = pushShiftChar(i, buffstr, 'i', 'I');
                break;
            case 24:
                i = pushShiftChar(i, buffstr, 'o', 'O');
                break;
            case 25:
                i = pushShiftChar(i, buffstr, 'p', 'P');
                break;
            case 26:
                i = pushShiftChar(i, buffstr, '[', '{');
                break;
            case 27:
                i = pushShiftChar(i, buffstr, ']', '}');
                break;
            case 28:				//This is the enter key, we need to add more functionality to it with Writer and other commands
                if (writing == 1)
	            {
	                printch('\n',0x0F);
        		    buffstr[i] = '\n';
	                i++;
	            }
	            else
	            {
	                reading = 0;
	            }
                break;
            case 30:
                if (ctrl == 1) {
   		            moveCursorX(-cursorX + 11);
                } else i = pushShiftChar(i, buffstr, 'a', 'A');
                break;
            case 31:
                i = pushShiftChar(i, buffstr, 's', 'S');
                break;
            case 32:
                i = pushShiftChar(i, buffstr, 'd', 'D');
                break;
            case 33:
                if (ctrl == 1) {
   		            moveCursorX(1);
                } else i = pushShiftChar(i, buffstr, 'f', 'F');
                break;
            case 34:
                i = pushShiftChar(i, buffstr, 'g', 'G');
                break;
            case 35:
                i = pushShiftChar(i, buffstr, 'h', 'H');
                break;
            case 36:
                i = pushShiftChar(i, buffstr, 'j', 'J');
                break;
            case 37:
                i = pushShiftChar(i, buffstr, 'k', 'K');
                break;
            case 38:
                i = pushShiftChar(i, buffstr, 'l', 'L');
                break;
            case 39:
                i = pushShiftChar(i, buffstr, ';', ':');
                break;
            case 40:
                i = pushShiftChar(i, buffstr, '\'', '"');
                break;
            case 41:
                i = pushShiftChar(i, buffstr, '`', '~');
                break;
	        case 42:        //Left shift 
                lshift = 1;
                break;
            case 43:        // \ for english keyboard
                i = pushShiftChar(i, buffstr, '\\', '|');
                break;
            case 44:        // z or Ctrl-Z
   		        if (ctrl == 1) {
   		            if (writing == 1) {
	    	            progexit = 1;
    		            reading = 0;
		                //writing = 0;
		            } else i = pushCtrlChar(i, buffstr, 'Z');
        		} else i = pushShiftChar(i, buffstr, 'z', 'Z');
                break;
            case 45:
                i = pushShiftChar(i, buffstr, 'x', 'X');
                break;
            case 46:
                i = pushShiftChar(i, buffstr, 'c', 'C');
                break;
            case 47:
                i = pushShiftChar(i, buffstr, 'v', 'V');
                break;
            case 48:
                if (ctrl == 1) {
   		            moveCursorX(-1);
                } else i = pushShiftChar(i, buffstr, 'b', 'B');
                break;
            case 49:
                i = pushShiftChar(i, buffstr, 'n', 'N');
                break;
            case 50:
                i = pushShiftChar(i, buffstr, 'm', 'M');
                break;
            case 51:
                i = pushShiftChar(i, buffstr, ',', '<');
                break;
            case 52:
                i = pushShiftChar(i, buffstr, '.', '>');
                break;
            case 53:
                i = pushShiftChar(i, buffstr, '/', '?');
                break;
            case 54:            // Right shift on
                rshift = 1;     // Toggle On
                break;
            case 55:            // (Keypad) *
                printch('*', 0x0F);
                buffstr[i] = '*';
                i++;
                break;
            case 56:            // Left/Right alt On
                alt = 1;        // Toggle On
                break;
            case 57:
                printch(' ', 0x0F);
                buffstr[i] = ' ';
                i++;
                break;
            case 58:            // Capslock down
                if (capslock == 0)
                    capslock = 1;   // Toggle On
    	        else capslock = 0;  // Toggle Off
                break;
	        case 72:
		        if (writing == 1)		//Up arrow
		        {
		            cursorY = cursorY - 1;
		            cursorX = cursorX - 1;
	            }
		        break;
	        case 75:				//Left Arrow
	            moveCursorX(-1);
	    	    break;
    	    case 77:				//Right Arrow
                moveCursorX(1);
	    	    break;
	        case 80:				//Down Arrow
	    	    if (writing == 1)
	    	    {
	    	      cursorY = cursorY + 1;
	    	      cursorX = cursorX - 1;
	    	    }
	    	    break;
	    	case 170:           // Left shift released (http://wiki.osdev.org/PS2_Keyboard)
	    	    lshift = 0;     // Toggle Off
	    	    break;
	    	case 182:           // Right shift released (http://wiki.osdev.org/PS2_Keyboard)
	    	    rshift = 0;     // Toggle Off
	    	    break;
            case 184:           // Left/Right alt Off
                alt = 0;        // Toggle Off
                break;
    	    }
        }
    }
    buffstr[i] = 0;                   
    return buffstr;
}
