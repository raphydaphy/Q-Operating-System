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

    //allocate some memory for command string buffer. 1kB should be enough for now
    const int bufSize = 128;
    char bufStr[bufSize];//Store sanitized user command (no arguments)
    char rawCommand[bufSize];//Gets user raw command from command line
    char arguments[bufSize/2][bufSize/2];//Store command arguments
    int fs = 1;//First space (first word means actual command)
    int ay = -1;//Y location for arguments
    int ax = 0;//X location for argumetns

    //prepare variable
    for(int i = 0; i < bufSize; ++i)
    {
        bufStr[i] = 0;
    }
    for(int y = 0; y < bufSize; ++y)
    {
        for(int x = 0; x < bufSize; ++x)
        {
            arguments[y][x] = 0;
        }
    }

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",white);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat\nsystem\ncalc\nme\ntest", white);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", white);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SEARCHFOR string searchTerm = (string) kmalloc(bufSize * sizeof(char)); print("\nDictionary File Name>  ", white); readStr(bufStr, bufSize); print("\nSearch Term>  ", green); readStr(searchTerm, bufSize); if (findInDictionary(bufStr,searchTerm)) { print("\nWe found the word!",white); }
    #define CMDNOTFOUND print("\n", white); print(bufStr, white); print(": Command Not Found ", white);

    while (true)
    {
        print("\nQ-Kernel>  ", light_grey);
        typingCmd = true;
        newCmd = true;
        readStr(rawCommand, bufSize);
        typingCmd = false;

    	for(int i = 0; i < bufSize; ++i)
        {
    	    bufStr[i] = 0;
        }
    	for(int y = 0; y < bufSize; ++y)
        {
            for(int x = 0; x < bufSize; ++x)
            {
                arguments[y][x] = 0;
            }
        }
    	fs = 1;
        ay = -1;
        ax = 0;
        if(MULTI_ARG_DEBUG == true)
        {
            //Sanitize raw input. Move first word to bufStr and move the rest of the word to arguments
            for(int i = 0; i < bufSize; ++i)
            {
                if(rawCommand[i] != 0 || rawCommand[i] != 10)
                {
                    if(fs == 1)
                    {
                        bufStr[i] = rawCommand[i];
                    }
                    else if(fs == 0)
                    {
                        arguments[ay][ax] = rawCommand[i];
                    }

                    if(i < bufSize && rawCommand[i+1] == 32)
                    {
          		        fs = 0;
          		        ay++;
          		    }
    	        }
                else break;
    	    }
        }
        else
        {
            //Sanitize raw input. Move first word to bufStr and move the rest of the word to arguments
            for(int i = 0; i < bufSize; ++i)
            {
                if(rawCommand[i] != 0 || rawCommand[i] != 10)
                {
                    if(fs == 1)
                    {
                        bufStr[i] = rawCommand[i];
                    }
                    if(i < bufSize && rawCommand[i+1] == 32)
                    {
                        fs = 0;
                        ay++;
                        ax = 0;
                    }
                }
                else if(fs == 0)
                {
                    arguments[ay][ax] = rawCommand[i];
                    ax++;
                }
                //}
                else
                {
                    break;
                }
            }
        }

        if (streql(strTrim(bufStr), ""))            {   HELP;                   }
        else if(streql(bufStr, "help"))             {   BIGHELP;                }
        else if(streql(bufStr, "system"))           {   system(rawCommand);     }
        else if(streql(bufStr, "skip"))             {   skip(rawCommand);       }
        else if(streql(bufStr, "files"))            {   files(rawCommand);      }
        else if(streql(bufStr, "cat"))              {   cat(rawCommand);        }
        else if(streql(bufStr,"execute"))           {   execute();              }
        else if(streql(bufStr,"switch"))            {   SWITCHDIR;              }
        else if(streql(bufStr,"writer"))            {   writer(arguments[0]);   }
        else if(streql(bufStr, "calc"))             {   calc(rawCommand);       }
        else if(streql(bufStr, "clear"))            {   clearScreen();          }
        else if(streql(bufStr, "test"))             {   test(arguments[0]);     }
        else if(streql(bufStr, "newdir"))           {   MKDIR;                  }
        else if(streql(bufStr, "erase"))            {   RMFILE;                 }
    	else if(streql(bufStr, "me"))               {   me(rawCommand);         }
    	else if(streql(bufStr, "search"))           {   SEARCHFOR;              }
        else if(streql(bufStr, "fill"))             { paintScreen(screen_color);}
        else                                        {   CMDNOTFOUND;            }
        newline();
    }
}
