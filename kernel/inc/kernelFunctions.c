#include "kernelFunctions.h"
#include "math.h"

#define MULTI_ARG_DEBUG false

void printIntro()
{
    // Some good colors for background: 66, 88, 99, CC, EE
    paintScreen(screen_color);

    // Made the intro beautiful
    drawFrame(header_background, 0, 0, 80, 4);
    printAt("Welcome to Q OS\r\n", header_foreground, 1, 1);
    printAt("You are using version 0.06",desc_foreground,1,2);

    newline();
    newline();
    newline();
}

void launchShell()
{
    // Setup all Q Kernel Stuff
    initialize_calc();

    //allocate some memory for command string cmdfer. 1kB should be enough for now
    const int cmdSize = 128;

    //Store sanitized user command (no arguments)
    char cmdStr[cmdSize];

    //Gets user raw command from command line
    char fullArgs[cmdSize];

    //First space (first word means actual command)
    int fs = 1;

    //Y location for arguments
    int ay = -1;

    //prepare variable
    for(int i = 0; i < cmdSize; ++i)
    {
        cmdStr[i] = 0;
    }

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",white);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat\nsystem\ncalc\nme\ntest", white);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", white);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SEARCHFOR string searchTerm = (string) kmalloc(cmdSize * sizeof(char)); print("\nDictionary File Name>  ", white); readStr(cmdStr, cmdSize); print("\nSearch Term>  ", green); readStr(searchTerm, cmdSize); if (findInDictionary(cmdStr,searchTerm)) { print("\nWe found the word!",white); }
    #define CMDNOTFOUND print("\n", white); print(cmdStr, white); print(": Command Not Found ", white);

    while (true)
    {
        printIntro();

        drawFrame(screen_background, 0, 4, 80, sh - 1);
        printAt("Q-Kernel>  ", light_grey, 1, 5);

        cursorY = 5;
        cursorX = 13;
        updateCursor();

        typingCmd = true;
        newCmd = true;

        readStr(fullArgs, cmdSize);

        typingCmd = false;

        for(int i = 0; i < cmdSize; ++i)
        {
            cmdStr[i] = 0;
        }

        fs = 1;
        ay = -1;

        //Sanitize raw input. Move first word to cmdStr
        for(int i = 0; i < cmdSize; ++i)
        {
            if(fullArgs[i] != 0 || fullArgs[i] != 10)
            {
                if(fs == 1)
                {
                    cmdStr[i] = fullArgs[i];
                }
                if(i < cmdSize && fullArgs[i+1] == 32)
                {
                    fs = 0;
                    ay++;
                }
            }
            else
            {
                break;
            }
        }

        if (streql(strTrim(cmdStr), ""))            {   HELP;                   }
        else if(streql(cmdStr, "help"))             {   BIGHELP;                }
        else if(streql(cmdStr, "system"))           {   system(fullArgs);     }
        else if(streql(cmdStr, "skip"))             {   skip(fullArgs);       }
        else if(streql(cmdStr, "files"))            {   files(fullArgs);      }
        else if(streql(cmdStr, "cat"))              {   cat(fullArgs);        }
        else if(streql(cmdStr,"execute"))           {   execute();              }
        else if(streql(cmdStr,"switch"))            {   SWITCHDIR;              }
        else if(streql(cmdStr,"writer"))            {   writer(fullArgs);   }
        else if(streql(cmdStr, "calc"))             {   calc(fullArgs);       }
        else if(streql(cmdStr, "clear"))            {   clearScreen();          }
        else if(streql(cmdStr, "test"))             {   test(fullArgs);       }
        else if(streql(cmdStr, "newdir"))           {   MKDIR;                  }
        else if(streql(cmdStr, "erase"))            {   RMFILE;                 }
    	else if(streql(cmdStr, "me"))               {   me(fullArgs);         }
    	else if(streql(cmdStr, "search"))           {   SEARCHFOR;              }
        else                                        {   CMDNOTFOUND;            }
        newline();
    }


}
