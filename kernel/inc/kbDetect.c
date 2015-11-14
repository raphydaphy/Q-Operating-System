#include "kbDetect.h"

string readStr()
{
    char buff;
    string buffstr;
    uint8 i = 0;
    uint8 reading = 1;
    while(reading)
    {
      //print(buffstr,0x0F);
      ctrl = 0;
	//exit the writer program when the enter key is pressed
	if (progexit == 1 && writing == 1)
	{
	  clearScreen();
	  updateCursor();
	  writing = 0;
	  progexit = 0;
	  print("Q-Kernel>  ",0x08);
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
	
        case 29:
		ctrl = 1;
		if (writing == 1) {
		  progexit = 1;
		  reading = 0;
		  //writing = 0;
		}
                break;
        case 1:
                print("\n\nProgram Needs To Exit Here...\n",0x0F);           //Escape button
                //buffstr[i] = (char)27;
                i++;
                break;
        case 2:
                printch('1',0x0F);
                buffstr[i] = '1';
                i++;
                break;
        case 3:
                printch('2',0x0F);
                buffstr[i] = '2';
                i++;
                break;
        case 4:
                printch('3',0x0F);
                buffstr[i] = '3';
                i++;
                break;
        case 5:
                printch('4',0x0F);
                buffstr[i] = '4';
                i++;
                break;
        case 6:
                printch('5',0x0F);
                buffstr[i] = '5';
                i++;
                break;
        case 7:
                printch('6',0x0F);
                buffstr[i] = '6';
                i++;
                break;
        case 8:
                printch('7',0x0F);
                buffstr[i] = '7';
                i++;
                break;
        case 9:
                printch('8',0x0F);
                buffstr[i] = '8';
                i++;
                break;
        case 10:
                printch('9',0x0F);
                buffstr[i] = '9';
                i++;
                break;
        case 11:
                printch('0',0x0F);
                buffstr[i] = '0';
                i++;
                break;
        case 12:
                printch('-',0x0F);
                buffstr[i] = '-';
                i++;
                break;
        case 13:
                printch('=',0x0F);
                buffstr[i] = '=';
                i++;
                break;
        case 14:
                printch('\b',0x0F);
                i--;
                buffstr[i] = 0;
                break;
        case 15:
                printch('\t',0x0F);          //Tab button
                buffstr[i] = '\t';
                i++;
                break;
        case 16:
                printch('q',0x0F);
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
                printch('w',0x0F);
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                printch('e',0x0F);
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                printch('r',0x0F);
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                printch('t',0x0F);
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                printch('y',0x0F);
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                printch('u',0x0F);
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                printch('i',0x0F);
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
		printch('o',0x0F);
		buffstr[i] = 'o';
		i++;
                break;
        case 25:
                printch('p',0x0F);
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
                printch('[',0x0F);
                buffstr[i] = '[';
                i++;
                break;
        case 27:
                printch(']',0x0F);
                buffstr[i] = ']';
                i++;
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
                printch('a',0x0F);
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
		printch('s',0x0F);
                buffstr[i] = 's';
                i++;	 
                break;
        case 32:
                printch('d',0x0F);
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                printch('f',0x0F);
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                printch('g',0x0F);
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
                printch('h',0x0F);
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
                printch('j',0x0F);
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
                printch('k',0x0F);
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
                printch('l',0x0F);
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
                printch(';',0x0F);
                buffstr[i] = ';';
                i++;
                break;
        case 40:
                printch((char)44,0x0F);               //   Single quote (')
                buffstr[i] = (char)44;
                i++;
                break;
        case 41:
                printch((char)44,0x0F);               // Back tick (`)
                buffstr[i] = (char)44;
                i++;
                break;
	case 42:                                 //Left shift 
                print("Left Shift was pressed, we need to put letters in CAPS while it is held down.",0x0F);
                buffstr[i] = 'q';
                i++;
                break;
        case 43:                                 //\ (< for somekeyboards)   
                printch((char)92,0x0F);
                buffstr[i] = 'q';
                i++;
                break;
        case 44:
                printch('z',0x0F);
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
                printch('x',0x0F);
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
                printch('c',0x0F);
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
                printch('v',0x0F);
                buffstr[i] = 'v';
                i++;
                break;                
        case 48:
                printch('b',0x0F);
                buffstr[i] = 'b';
                i++;
                break;               
        case 49:
                printch('n',0x0F);
                buffstr[i] = 'n';
                i++;
                break;                
        case 50:
                printch('m',0x0F);
                buffstr[i] = 'm';
                i++;
                break;               
        case 51:
                printch(',',0x0F);
                buffstr[i] = ',';
                i++;
                break;                
        case 52:
                printch('.',0x0F);
                buffstr[i] = '.';
                i++;
                break;            
        case 53:
                printch('/',0x0F);
                buffstr[i] = '/';
                i++;
                break;            
        case 54:
                printch('.',0x0F);
                buffstr[i] = '.';
                i++;
                break;            
        case 55:
                printch('/',0x0F);
                buffstr[i] = '/';
                i++;
                break;            
      case 56:
                print("RightShift was pressed, while it is held down letters should be in CAPS.",0x0F);          // Right shift
                buffstr[i] = ' ';
                i++;
                break;           
        case 57:
                printch(' ',0x0F);
                buffstr[i] = ' ';
                i++;
                break;
	case 72:
		if (writing == 1)		//Up arrow
		{
		  cursorY = cursorY - 1;
		  cursorX = cursorX - 1;
		}
		break;
	case 75:				//Left Arrow
		if (writing == 1)
		{
		  cursorX = cursorX - 1;
		  //cursorY = cursorY - 1;
		}
		break;
	case 77:				//Right Arrow
		if (writing == 1)
		{
		  cursorX = cursorX + 1;
		  //cursorY = cursorY - 1;
		}
		break;
	case 80:				//Down Arrow
		if (writing == 1)
		{
		  cursorY = cursorY + 1;
		  cursorX = cursorX - 1;
		}
		break;
            }
        }
        if (ctrl == 1)
	{
	  print("Ctrl = 1 ",0x0F);
	}
    }
    buffstr[i] = 0;                   
    return buffstr;
}
