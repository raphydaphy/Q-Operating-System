#include "kernelFunctions.h"
#include "math.h"

#define MULTI_ARG_DEBUG false

void printIntro()
{
    // Some good colors for background: 66, 88, 99, CC, EE
    paintScreen(screen_color);

    // Made the intro beautiful
    drawFrame(header_background, 0, 0, 80, 4);
    printAt("                            Welcome to Q OS                                   \r\n", header_foreground, 1, 1);
    printAt("                      You are using version 0.06                              ",desc_foreground,1,2);

    newline();
    newline();
    newline();
}

void launchShell()
{
    initialize_calc();

    string rawInput;//Gets user raw command from command line
    list_t args;//Store command args

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",white);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat\nsystem\ncalc\nme\ntest", white);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", white);
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define CMDNOTFOUND print("\n", white); print(commandString, white); print(": Command Not Found ", red);
    #define SEARCHFOR string searchTerm = (string)kmalloc(BUFSIZE * sizeof(char)); print("\nDictionary File Name>  ", white); readStr(rawInput, BUFSIZE); print("\nSearch Term>  ", green); readStr(searchTerm, BUFSIZE); if (findInDictionary(rawInput,searchTerm)) { print("\nWe found the word!",white);}

    while (true)
    {
        print("\nQ-Kernel>  ", light_grey);
        typingCmd = true;
        newCmd = true;
        rawInput = (string) kmalloc(BUFSIZE * sizeof(char));
        args = list_init();
        readStr(rawInput, BUFSIZE);
        typingCmd = false;

        bool wordStarted = false;
        string tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
        for(uint8 i = 0; i < strlen(rawInput); i++)
        {
            if(isspace(rawInput[i]))
            {
                if(wordStarted)
                {
                    list_add(&args, tempArg);
                    wordStarted = false;
                    tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
                }
            }
            else
            {
                wordStarted = true;
                append(tempArg,rawInput[i]);
                if(i+1 == strlen(rawInput))
                {
                    list_add(&args, tempArg);
                    wordStarted = false;
                    tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
                }
            }
        }
        string commandString = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 0)
        {
            commandString = list_gets(args,0);
        }
        list_remove(&args,0);
        string firstArg = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 0)
        {
            firstArg = list_gets(args,0);
        }
        list_shrink(&args);
             if(streql(commandString, ""             )) {   HELP;                       }
        else if(streql(commandString, "help"         )) {   BIGHELP;                    }
        else if(streql(commandString, "system"       )) {   system(rawInput);           }
        else if(streql(commandString, "skip"         )) {   skip(rawInput);             }
        else if(streql(commandString, "files"        )) {   files(firstArg);            }
        else if(streql(commandString, "cat"          )) {   cat(rawInput);	            }
        else if(streql(commandString, "execute"      )) {   execute();                  }
        else if(streql(commandString, "switch"       )) {   SWITCHDIR;                  }
        else if(streql(commandString, "writer"       )) {   writer(firstArg);           }
        else if(streql(commandString, "calc"         )) {   calc(rawInput);           }
        else if(streql(commandString, "clear"        )) {   clearScreen();              }
        else if(streql(commandString, "test"         )) {   test(args);                 }
        else if(streql(commandString, "newdir"       )) {   MKDIR;                      }
        else if(streql(commandString, "erase"        )) {   RMFILE;                     }
	    else if(streql(commandString, "me"           )) {   me(rawInput);               }
	    else if(streql(commandString, "search"       )) {   SEARCHFOR;                  }
        else if(streql(commandString, "fill"         )) {   paintScreen(screen_color);  }
        else                                            {   CMDNOTFOUND;                }
        if(args.size > 0)
        {
            list_destroy(&args);
        }
    }
}
