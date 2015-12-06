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

    string rawInput;//Gets user raw command from command line
    list_t arguments;//Store command arguments

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",0x0F);
    #define HELP print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat\nsystem\ncalc\nme\ntest", 0x0F);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", 0x0F);
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define CMDNOTFOUND print("\n", 0x0F); print(rawInput, 0x0F); print(": Command Not Found ", 0x0F);
    #define SEARCHFOR string searchTerm = (string) kmalloc(BUFSIZE * sizeof(char)); print("\nDictionary File Name>  ", 0x0F); readStr(rawInput, BUFSIZE); print("\nSearch Term>  ", 0x0A); readStr(searchTerm, BUFSIZE); if (findInDictionary(rawInput,searchTerm)) { print("\nWe found the word!",0x0F); }

    while (true) {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        rawInput = (string) kmalloc(BUFSIZE * sizeof(char));
        arguments = list_init();
        readStr(rawInput, BUFSIZE);
        typingCmd = false;
        newCmd = true;
		newline();
        
        if (streql(rawInput, "\n"))        {   HELP;             }

        printint(strlen(rawInput), 0x0F);
        println("hello",0x0F);

        bool wordStarted = false;
        string tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
        for(uint8 i = 0; i < strlen(rawInput); i++){
            string hello = "";
            readStr(hello, 0);
			printint(i, 0x0F);
            newline();
            if(isspace(rawInput[i])){
                if(wordStarted){
				    println(tempArg, 0x0F);
                    list_add(&arguments, tempArg);
                    wordStarted = false;
                    tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
                }
            }else{
			    print(rawInput, 0x0F);
                println("|rawInput", 0x0F);
			    print(tempArg, 0x0F);
                println("|tempArg", 0x0F);
                wordStarted = true;
                char newChar = rawInput[i];
                tempArg[strlen(tempArg)] = newChar;
			    print(rawInput, 0x0F);
                println("|rawInput", 0x0F);
			    print(tempArg, 0x0F);
                println("|tempArg", 0x0F);
            }
        }
        println(tempArg, 0x0F);
        list_add(&arguments, tempArg);
        wordStarted = false;
        tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
        
        list_shrink(&arguments);

		println(itos(arguments.size,10),0x0F);
        //Testing Only
        for(uint8 i = 0; i < arguments.size; i++){
            println(list_gets(arguments,i), 0x0F);
        }

        string firstArgument = list_gets(arguments,0);
        if(streql(firstArgument, "help"))         {   BIGHELP;          }
        else if(streql(firstArgument, "system"))       {   system(rawInput);  }
        else if(streql(firstArgument, "skip"))         {   skip(rawInput);    }
        else if(streql(firstArgument, "files"))        {   files(list_get(arguments,1));          }
        else if(streql(firstArgument, "cat"))          {   cat(rawInput);			 }
        else if(streql(firstArgument,"execute"))       {   execute();        }
        else if(streql(firstArgument,"switch"))        {   SWITCHDIR;        }
        else if(streql(firstArgument,"writer"))        {   writer(list_get(arguments,1));   }
        else if(streql(firstArgument, "calc"))         {   calc(list_get(arguments,1));  }
        else if(streql(firstArgument, "clear"))        {   clearScreen();    }
        else if(streql(firstArgument, "test"))         {   test(list_get(arguments,1));  }
        else if(streql(firstArgument, "newdir"))       {   MKDIR;            }
        else if(streql(firstArgument, "erase"))        {   RMFILE;           }
	    else if(streql(firstArgument, "me"))           {   me(rawInput);         }
	    else if(streql(firstArgument, "search"))       {   SEARCHFOR;              }
        else                                           {   CMDNOTFOUND;            }
        newline();
    }
}
