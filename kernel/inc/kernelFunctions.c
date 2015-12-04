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

    string rawCommand;//Gets user raw command from command line
    list_t arguments = list_init();//Store command arguments

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",0x0F);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc", 0x0F);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SYSTEMMAN system(list_get(arguments,1));
    #define SAYHI print("\nHello!", 0x3F);
    #define CATFILE print("\nFile Name>  ", 0x0F); readStr(rawCommand, BUFSIZE); ASSERT(strlength(rawCommand) < MAX_FNAME_LEN); cat(finddir_fs(fs_root, rawCommand));
    #define SWITCHDIR print("\nThe specified directory was not found ", 0x0F);
    #define BIGCLEAR clearScreen(); printIntro();
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define SKIP skip(rawCommand);
    #define FILEMAN files(list_get(arguments,1));
    #define WRITE writer(list_get(arguments,1));
    #define ME me(rawCommand);
    #define CMDNOTFOUND print("\n", 0x0F); print(rawCommand, 0x0F); print(": Command Not Found ", 0x0F);

    while (true) {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        readStr(rawCommand, BUFSIZE);
        typingCmd = false;
		newline();

        if (strlength(rawCommand) == 0)        {   HELP;             }

		rawCommand += ' ';;

        bool wordStarted = false;
        string tempArgument = "";
        for(uint8 i = 0; i < strlength(rawCommand); i++){
			printint(i, 0x0F);
            if(isspace(rawCommand[i])){
                if(wordStarted){
                    list_add(&arguments, tempArgument);
                    wordStarted = false;
                    tempArgument = "";
                }
            }else{
                wordStarted = true;
                tempArgument += rawCommand[i];
				println(tempArgument, 0x0F);
            }
        }
        //list_shrink(&arguments);

		println(itos(arguments.size,10),0x0F);
        //Testing Only
        /*for(uint8 i = 0; i < arguments.size; i++){
            println(list_gets(arguments,i), 0x0F);
        }*/

        string firstArgument = list_gets(arguments,0);
        if(strEql(firstArgument, "help"))         {   BIGHELP;          }
        else if(strEql(firstArgument, "system"))       {   system(list_get(arguments,1));  }
        else if(strEql(firstArgument, "skip"))         {   SKIP;             }
        else if(strEql(firstArgument, "hi"))           {   SAYHI;            }
        else if(strEql(firstArgument, "files"))        {   FILEMAN;          }
        else if(strEql(firstArgument, "cat"))          {   CATFILE			 }
        else if(strEql(firstArgument,"execute"))       {   execute();        }
        else if(strEql(firstArgument,"switch"))        {   SWITCHDIR;        }
        else if(strEql(firstArgument,"writer"))        {   WRITE;            }
        else if(strEql(firstArgument, "calc"))         {   calc(list_get(arguments,1));  }
        else if(strEql(firstArgument, "clear"))        {   clearScreen();    }
        else if(strEql(firstArgument, "clear -i"))     {   BIGCLEAR;         }
        else if(strEql(firstArgument, "test"))         {   test(list_get(arguments,1));  }
        else if(strEql(firstArgument, "newdir"))       {   MKDIR;            }
        else if(strEql(firstArgument, "erase"))        {   RMFILE;           }
	    else if(strEql(firstArgument, "me"))           {   ME;               }
	    else if(strEql(firstArgument, "search"))
	    {
            string searchTerm = (string) kmalloc(BUFSIZE * sizeof(char));

	        print("\nDictionary File Name>  ", 0x0F);
	        readStr(rawCommand, BUFSIZE);
	        print("\nSearch Term>  ", 0x0A);

            readStr(searchTerm, BUFSIZE);

	        if (findInDictionary(rawCommand,searchTerm))
            {
                print("We found the word!",0x0F);
            }

	    }
        else                                    {   CMDNOTFOUND;      }
        newline();
    }
}
