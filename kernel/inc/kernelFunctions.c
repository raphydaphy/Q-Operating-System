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
    for(int i = 0; i < bufSize; ++i){
	bufStr[i] = 0;
    }
    for(int y = 0; y < bufSize; ++y){
	for(int x = 0; x < bufSize; ++x){
		arguments[y][x] = 0;
    	}
    }

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",0x0F);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc", 0x0F);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SYSTEMMAN system(arguments);
    #define SAYHI print("\nHello!", 0x3F);
    #define CATFILE print("\nFile Name>  ", 0x0F); readStr(bufStr, bufSize); ASSERT(strlength(bufStr) < MAX_FNAME_LEN); cat(finddir_fs(fs_root, bufStr));
    #define SWITCHDIR print("\nThe specified directory was not found ", 0x0F);
    #define CALCULATE calc(arguments);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SKIP skip(rawCommand);
    #define FILEMAN files(arguments);
    #define WRITE writer(arguments);
    #define ME me(rawCommand);
    #define CMDNOTFOUND print("\n", 0x0F); print(bufStr, 0x0F); print(": Command Not Found ", 0x0F);

    while (true) {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        readStr(rawCommand, bufSize);
        typingCmd = false;

    	for(int i = 0; i < bufSize; ++i){
    	    bufStr[i] = 0;
    	}
    	for(int y = 0; y < bufSize; ++y){
                for(int x = 0; x < bufSize; ++x){
    		arguments[y][x] = 0;
    	    }
    	}
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

        if (strEql(strTrim(bufStr), ""))        {   HELP;             }
        else if(strEql(bufStr, "help"))         {   BIGHELP;          }
        else if(strEql(bufStr, "system"))       {   SYSTEMMAN;        }
        else if(strEql(bufStr, "skip"))         {   SKIP;             }
        else if(strEql(bufStr, "hi"))           {   SAYHI;            }
        else if(strEql(bufStr, "files"))        {   FILEMAN;          }
        else if(strEql(bufStr, "cat"))          {   CATFILE;          }
        else if(strEql(bufStr,"execute"))       {   execute();        }
        else if(strEql(bufStr,"switch"))        {   SWITCHDIR;        }
        else if(strEql(bufStr,"writer"))        {   WRITE;            }
        else if(strEql(bufStr, "calc"))         {   CALCULATE;        }
        else if(strEql(bufStr, "clear"))        {   clearScreen();    }
        else if(strEql(bufStr, "clear -i"))     {   BIGCLEAR;         }
        else if(strEql(bufStr, "newdir"))       {   MKDIR;            }
        else if(strEql(bufStr, "erase"))        {   RMFILE;           }
	else if(strEql(bufStr, "me"))           {   ME;               }
	else if(strEql(bufStr, "search"))
	{
	    print("\nDictionary File Name>  ", 0x0F);
	    readStr(bufStr, bufSize);
	    ASSERT(strlength(bufStr) < MAX_FNAME_LEN);
	    findInDictionary(finddir_fs(fs_root, bufStr),1013,"ACCEPT");
	
	}
        else                                    {   CMDNOTFOUND;      }

        newline();
    }
}
