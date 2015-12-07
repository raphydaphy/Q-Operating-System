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
    list_t args;//Store command args

    #define TIP print("\nTip: If enter key does not work, it might mean that the input is too long",0x0F);
    #define HELP print("\nWorking Commands in Q OS: \n\twriter\n\tclear\n\texecute\n\thi\n\tskip\n\tfiles\n\tcat\n\tsystem\n\tcalc\n\tme\n\ttest", 0x0F);
    #define BIGHELP kbHelp(); TIP; HELP;
    #define SWITCHDIR print("\nThe specified directory was not found ", 0x0F);
    #define MKDIR print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define RMFILE print("\nThis Command is Reserved for when we have a FAT32 or better FileSystem...", 0x3F);
    #define CMDNOTFOUND newline(); print(commandString, 0x0F); print(": Command Not Found ", 0x04);
    #define SEARCHFOR string searchTerm = (string) kmalloc(BUFSIZE * sizeof(char)); print("\nDictionary File Name>  ", 0x0F); readStr(rawInput, BUFSIZE); print("\nSearch Term>  ", 0x0A); readStr(searchTerm, BUFSIZE); if (findInDictionary(rawInput,searchTerm)) { print("\nWe found the word!",0x0F); }

    while (true) {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        rawInput = (string) kmalloc(BUFSIZE * sizeof(char));
        args = list_init();
        readStr(rawInput, BUFSIZE);
        typingCmd = false;

        bool wordStarted = false;
        string tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
        for(uint8 i = 0; i < strlen(rawInput); i++){
            if(isspace(rawInput[i])){
                if(wordStarted){
                    list_add(&args, tempArg);
                    wordStarted = false;
                    tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
                }
            }else{
                wordStarted = true;
                append(tempArg,rawInput[i]);
                if(i+1 == strlen(rawInput)){
                    list_add(&args, tempArg);
                    wordStarted = false;
                    tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
                }
            }
        }
        string commandString = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 0){
            commandString = list_gets(args,0);
        }
        list_remove(&args,0);
        string firstArg = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 0){
            firstArg = list_gets(args,0);
        }
        list_shrink(&args);
             if(streql(commandString, ""             )) {   HELP;             }
        else if(streql(commandString, "help"         )) {   BIGHELP;          }
        else if(streql(commandString, "system"       )) {   system(rawInput); }
        else if(streql(commandString, "skip"         )) {   skip(rawInput);   }
        else if(streql(commandString, "files"        )) {   files(firstArg);  }
        else if(streql(commandString, "cat"          )) {   cat(rawInput);	  }
        else if(streql(commandString, "execute"      )) {   execute();        }
        else if(streql(commandString, "switch"       )) {   SWITCHDIR;        }
        else if(streql(commandString, "writer"       )) {   writer(firstArg); }
        else if(streql(commandString, "calc"         )) {   calc(firstArg);   }
        else if(streql(commandString, "clear"        )) {   clearScreen();    }
        else if(streql(commandString, "test"         )) {   test(args);       }
        else if(streql(commandString, "newdir"       )) {   MKDIR;            }
        else if(streql(commandString, "erase"        )) {   RMFILE;           }
	    else if(streql(commandString, "me"           )) {   me(rawInput);     }
	    else if(streql(commandString, "search"       )) {   SEARCHFOR;        }
        else                                            {   CMDNOTFOUND;      }
        if(args.size > 0){
            list_destroy(&args);
        }
    }
}
