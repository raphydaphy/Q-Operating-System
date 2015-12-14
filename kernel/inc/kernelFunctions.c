#include "kernelFunctions.h"

#define MULTI_ARG_DEBUG false

stackVM_t currentEnv;

void launchShell()
{
    // Setup all Q Kernel Stuff
    initialize_calc();

    // Setup all StackVM
    currentEnv = initEnv(64);

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

    // the Y locaiton to print cmd line text
    actualY = 4;

    //prepare variable
    for(int i = 0; i < cmdSize; ++i)
    {
        cmdStr[i] = 0;
    }

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",white);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nskip\nfiles\ncat\nsystem\ncalc\nme\ntest", white);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", white);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SEARCHFOR string searchTerm = (string) kmalloc(cmdSize * sizeof(char)); print("\nDictionary File Name>  ", white); readStr(cmdStr, cmdSize, false); print("\nSearch Term>  ", green); readStr(searchTerm, cmdSize, false); if (findInDictionary(cmdStr,searchTerm)) { print("\nWe found the word!",white); }
    #define CMDNOTFOUND print("\n", white); print(cmdStr, white); print(": Command Not Found ", white);

    printIntro();

    drawBorder(screen_background, 0, 4, 80, sh - 1);

    setup();

    while (true)
    {
        if (loggedIn)
        {
            actualY++;

            printAt("Q-Kernel>  ", light_grey, 1, actualY);

            cursorY = startCmdY = actualY;
            cursorX = deleteStopX = 12;
            updateCursor();

            typingCmd = true;
            newCmd = true;

            readStr(fullArgs, cmdSize, false);

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
            else if(streql(cmdStr, "system"))           {   system(fullArgs);       }
            else if(streql(cmdStr, "skip"))             {   skip(fullArgs);         }
            else if(streql(cmdStr, "files"))            {   files(fullArgs);        }
            else if(streql(cmdStr, "cat"))              {   cat(fullArgs);          }
            else if(streql(cmdStr,"execute"))           {   execute(fullArgs);      }
            else if(streql(cmdStr,"switch"))            {   SWITCHDIR;              }
            else if(streql(cmdStr,"writer"))            {   writer(fullArgs);       }
            else if(streql(cmdStr, "calc"))             {   calc(fullArgs);         }
            else if(streql(cmdStr, "tedi"))             {   tedi_session();         }
            else if(streql(cmdStr, "clear"))            {   clearScreen();          }
            else if(streql(cmdStr, "test"))             {   test(fullArgs);         }
            else if(streql(cmdStr, "newdir"))           {   MKDIR;                  }
            else if(streql(cmdStr, "erase"))            {   RMFILE;                 }
        	else if(streql(cmdStr, "me"))               {   me(fullArgs);           }
        	else if(streql(cmdStr, "hi"))               {   hi(fullArgs);           }
        	else if(streql(cmdStr, "search"))           {   SEARCHFOR;              }
        	else if(streql(cmdStr, "svm"))              {
        	    int ops[] = {
        	        pushi, 1,       // Pushes 1
        	        pushd, 0, 5,    // Pushes 0.5
        	        swap,           // 1, 0.5 -> 0.5, 1
        	        ci_d,           // 1 -> 1.0
        	        addd,           // 0.5 + 1
        	        pushd, 1, 0,    // Pushes 1.0
        	        subd,           // 1.5 - 1.0
        	        pushd, 3, 0,    // Pushes 3.0
        	        muld,           // 0.5 * 3
        	        pushd, 3, 0,    // Pushes 3.0
        	        divd,           // 1.5 / 3.0
        	        EOS             // End of prog
    	        };
        	    invokeOp(&currentEnv, ops, false);
    	    }
            else                                        {   CMDNOTFOUND;            }
            newline();
        }
        else
        {
            login();
        }

    }
}
