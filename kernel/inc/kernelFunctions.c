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
    string cmdStr = NULL;

    //Gets user raw command from command line
    string fullArgs = NULL;

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
    #define SEARCHFOR string searchTerm = NULL; print("\nDictionary File Name>  ", white); cmdStr = readstr(); print("\nSearch Term>  ", green); searchTerm = readstr(); if (findInDictionary(cmdStr,searchTerm)) { print("\nWe found the word!",white); }
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

            fullArgs = toUpper(readstr());

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
            else if(streql(cmdStr, "HELP"))             {   BIGHELP;                }
            else if(streql(cmdStr, "SYSTEM"))           {   system(fullArgs);       }
            else if(streql(cmdStr, "SKIP"))             {   skip(fullArgs);         }
            else if(streql(cmdStr, "FILES"))            {   files(fullArgs);        }
            else if(streql(cmdStr, "CAT"))              {   cat(fullArgs);          }
            else if(streql(cmdStr,"EXECUTE"))           {   execute(fullArgs);      }
            else if(streql(cmdStr,"SWITCH"))            {   SWITCHDIR;              }
            else if(streql(cmdStr,"WRITER"))            {   writer(fullArgs);       }
            else if(streql(cmdStr, "CALC"))             {   calc(fullArgs);         }
            else if(streql(cmdStr, "CLEAR"))            {   clearScreen();          }
            else if(streql(cmdStr, "TEST"))             {   test(fullArgs);         }
            else if(streql(cmdStr, "NEWDIR"))           {   MKDIR;                  }
            else if(streql(cmdStr, "ERASE"))            {   RMFILE;                 }
        	else if(streql(cmdStr, "ME"))               {   me(fullArgs);           }
        	else if(streql(cmdStr, "HI"))               {   hi(fullArgs);           }
        	else if(streql(cmdStr, "SEARCH"))           {   SEARCHFOR;              }
            else if(streql(cmdStr, "PAINTER"))          {   painter(fullArgs);      }
            else if(streql(cmdStr, "PCI"))              {   pciInit();              }
        	else if(streql(cmdStr, "SVM"))              {
        	    string hworld = "Hello, world!";
        	    int ops[] = {
        	        blnk,           // Clears the terminal
        	        pushi, 1,       // Pushes 1
        	        pushf, 0, 5,    // Pushes 0.5
        	        swap,           // 1, 0.5 -> 0.5, 1
        	        ci_f,           // 1 -> 1.0
        	        addf,           // 0.5 + 1
        	        pushf, 1, 0,    // Pushes 1.0
        	        subf,           // 1.5 - 1.0
        	        pushf, 3, 0,    // Pushes 3.0
        	        mulf,           // 0.5 * 3
        	        pushf, 3, 0,    // Pushes 3.0
        	        divf,           // 1.5 / 3.0

                    seto, 2, 8,     // new label for div. Jumps to opcode clrs
                    tryl, 2,
                    setl, 0,        // new label 0
                    pushf, 0, 0,    // Pushes 0.0
                    divf,           // 0.5 / 0.0

                    clrs,           // Clears stack
                    pushi, 0,       // Pushes 0
                    pushi, 10,      // Pushes 10
                    raddi,          // 0 +...+10
                    pushi, 55,
                    eqlv,           // Test to see if result is same

                    seto, 3, 1,     // new label for CPU halt simulation
                    notb,           // Flip the value
                    ifjl, 3,        // (Translated) if (55 != 55) goto label 3
                    jmpo, 3,        // (Translated) else move out of the way
                    _hlt,           // GG
                    jmpl, 3,        // jmp label 3

                    pushi, 0xA,     // Pushes 10
                    defi, 0,        // "0" -> 10
                    geti, 0,        // Getting value of "0"
                    pushi, 0x01,    // Pushes 0x01
                    infbc,          // Prints in messagebox
                    pushs, (int)
                        hworld,     // Pushes string reference
                    defs, 5,        // Assign it to map
                    gets, 5,        // Retrieves the value immediately
                    infbs,
                    pushf, 3, -1, 5,// Pushes 3.05
                    infbf,

                    pushi, 2, waiti,// Pause for 2 seconds

        	        EOS             // End of prog
    	        };
        	    invokeOp(&currentEnv, ops);
        	    cleanEnv(&currentEnv);
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
