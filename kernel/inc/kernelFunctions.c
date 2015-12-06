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
    #define CMDNOTFOUND newline(); print(firstArg, 0x0F); print(": Command Not Found ", 0x04);
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
            }
        }
        if(wordStarted){
            list_add(&args, tempArg);
            wordStarted = false;
            tempArg = (string) kmalloc(BUFSIZE * sizeof(char));
        }
        
        list_shrink(&args);
        string firstArg = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 0){
            firstArg = list_gets(args,0);
        }
        string secondArg = (string) kmalloc(BUFSIZE * sizeof(char));
        if(args.size > 1){
            secondArg = list_gets(args,1);
        }
             if(streql(firstArg, ""             )) {   HELP;             }
        else if(streql(firstArg, "help"         )) {   BIGHELP;          }
        else if(streql(firstArg, "system"       )) {   system(rawInput); }
        else if(streql(firstArg, "skip"         )) {   skip(rawInput);   }
        else if(streql(firstArg, "files"        )) {   files(secondArg); }
        else if(streql(firstArg, "cat"          )) {   cat(rawInput);	}
        else if(streql(firstArg, "execute"      )) {   execute();        }
        else if(streql(firstArg, "switch"       )) {   SWITCHDIR;        }
        else if(streql(firstArg, "writer"       )) {   writer(secondArg);}
        else if(streql(firstArg, "calc"         )) {   calc(secondArg);  }
        else if(streql(firstArg, "clear"        )) {   clearScreen();    }
        else if(streql(firstArg, "test"         )) {   test(secondArg);  }
        else if(streql(firstArg, "newdir"       )) {   MKDIR;            }
        else if(streql(firstArg, "erase"        )) {   RMFILE;           }
	    else if(streql(firstArg, "me"           )) {   me(rawInput);     }
	    else if(streql(firstArg, "search"       )) {   SEARCHFOR;        }
        else                                       {   CMDNOTFOUND;      }
        list_destroy(&args);
    }
}
