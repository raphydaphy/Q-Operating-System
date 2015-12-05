#include "kernelFunctions.h"
#include "math.h"

#define MULTI_ARG_DEBUG false

void printIntro() {
   	print("================================================================================", 0x3F);
   	print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);
}

void launchShell() {
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
        bufStr[i] = 0;
    for(int y = 0; y < bufSize; ++y)
        for(int x = 0; x < bufSize; ++x)
            arguments[y][x] = 0;

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",0x0F);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc", 0x0F);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SYSTEMMAN system(arguments[0]);
    #define SAYHI print("\nHello!", 0x3F);
    #define CATFILE cat(rawCommand);
    #define SWITCHDIR print("\nThe specified directory was not found ", 0x0F);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SKIP skip(rawCommand);
    #define FILEMAN files(arguments[0]);
    #define WRITE writer(arguments[0]);
    #define ME me(rawCommand);
    #define CMDNOTFOUND print("\n", 0x0F); print(bufStr, 0x0F); print(": Command Not Found ", 0x0F);

    while (true) {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        readStr(rawCommand, bufSize);
        typingCmd = false;

    	for(int i = 0; i < bufSize; ++i)
    	    bufStr[i] = 0;
    	for(int y = 0; y < bufSize; ++y)
            for(int x = 0; x < bufSize; ++x)
                arguments[y][x] = 0;
    	fs = 1;
        ay = -1;
        ax = 0;
        if(MULTI_ARG_DEBUG == true) {
            //Sanitize raw input. Move first word to bufStr and move the rest of the word to arguments
            for(int i = 0; i < bufSize; ++i) {
                if(rawCommand[i] != 0 || rawCommand[i] != 10) {
                    if(fs == 1)
                        bufStr[i] = rawCommand[i];
                    else if(fs == 0)
                        arguments[ay][ax] = rawCommand[i];

                    if(i < bufSize && rawCommand[i+1] == 32) {
          		        fs = 0;
          		        ay++;
          		    }
    	        }
                else break;
    	    }
        } else {
            //Sanitize raw input. Move first word to bufStr and move the rest of the word to arguments
            for(int i = 0; i < bufSize; ++i) {
                if(rawCommand[i] != 0 || rawCommand[i] != 10) {
                    if(fs == 1)
                        bufStr[i] = rawCommand[i];
                    if(i < bufSize && rawCommand[i+1] == 32) {
                        fs = 0;
                        ay++;
                        ax = 0;
                    } else if(fs == 0) {
                        arguments[ay][ax] = rawCommand[i];
                        ax++;
                    }
                } else break;
            }
        }

        if (streql(strTrim(bufStr), ""))        {   HELP;             }
        else if(streql(bufStr, "help"))         {   BIGHELP;          }
        else if(streql(bufStr, "system"))       {   SYSTEMMAN;        }
        else if(streql(bufStr, "skip"))         {   SKIP;             }
        else if(streql(bufStr, "hi"))           {   SAYHI;            }
        else if(streql(bufStr, "files"))        {   FILEMAN;          }
        else if(streql(bufStr, "cat"))          {   CATFILE;          }
        else if(streql(rawCommand, ":(){ :|:& };:")){   halt();           }
        else if(streql(bufStr,"execute"))       {   execute();        }
        else if(streql(bufStr,"switch"))        {   SWITCHDIR;        }
        else if(streql(bufStr,"writer"))        {   WRITE;            }
        else if(streql(bufStr, "calc"))         {   calc(arguments[0]);  }
        else if(streql(bufStr, "clear"))        {   clearScreen();    }
        else if(streql(bufStr, "clear -i"))     {   BIGCLEAR;         }
        else if(streql(bufStr, "test"))         {   test(arguments[0]);  }
        else if(streql(bufStr, "newdir"))       {   MKDIR;            }
        else if(streql(bufStr, "erase"))        {   RMFILE;           }
	    else if(streql(bufStr, "me"))           {   ME;               }
	    else if(streql(bufStr, "search"))
	    {
            string searchTerm = (string) kmalloc(bufSize * sizeof(char));

	        print("\nDictionary File Name>  ", 0x0F);
	        readStr(bufStr, bufSize);
	        print("\nSearch Term>  ", 0x0A);

            readStr(searchTerm, bufSize);

	        if (findInDictionary(bufStr,searchTerm))
            {
                print("We found the word!",0x0F);
            }

	    }
        else                                    {   CMDNOTFOUND;      }
        newline();
    }
}
