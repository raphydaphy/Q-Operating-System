#include "../multiboot.h"

#include "kernelFunctions.h"
#include "fs.h"
#include "timer.h"
#include "error.h"
#include "paging.h"
#include "initrd.h"
#include "kbDetect.h"
#include "descriptorTables.h"
#include "assemblyFunctions.h"

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc"
#define PRO_TIP "\nTip: If enter key does not work, it might mean that the input is too long"

void printIntro(){
   	print("================================================================================", 0x3F);
   	print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);
}

void launchShell() {
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

    while (true)
    {
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

	//Sanitize raw input. Move first word to bufStr and move the rest of the word to arguments
	for(int i = 0; i < bufSize; ++i){
	    if(rawCommand[i] != 0 || rawCommand[i] != 10){
		if(fs == 1)
		    bufStr[i] = rawCommand[i];
		if(i < bufSize && rawCommand[i+1] == 32){
		    fs = 0;
		    ay++;
		    ax = 0;
		}
		
		else if(fs == 0){
		    arguments[ay][ax] = rawCommand[i];
		    ax++;
		}
	    }else{
	    	break;
	    }
	}

        if (strEql(strTrim(bufStr), ""))
        {
            print(COMMAND_HELP, 0x0F);
        }
        else if(strEql(bufStr, "help"))
        {
            kbHelp();
            println(PRO_TIP, 0x0F);
            print(COMMAND_HELP, 0x0F);
        }
        else if(strEql(bufStr, "system")){
	    print("\nSystem Utility\nCurrently only able to reboot and halt system.\nHard shutdown to power off.\n\nMenu:\n1. [reboot]\n2. [halt]\n3. [shutdown]\n> ", 0x0F);
	    readStr(bufStr, bufSize);
	    if(strEql(bufStr, "reboot"))
            {
                //reboots the computer
                reboot();
            }
	    else if(strEql(bufStr, "halt"))
            {
                //halts the computer
                halt();
            }
	    else if(strEql(bufStr, "shutdown"))
            {
                //shutdown the computer
                shutdown();
            }
	}
        else if(strEql(bufStr, "skip"))
        {
            // It literally does nothing... (Useful at callback)
        }
        else if(strEql(bufStr, "hi"))
        {
            print("\nHello!", 0x3F);
        }
        else if(strEql(bufStr, "files")) { files(); }
        else if(strEql(bufStr, "cat"))
        {
            print("\nFile Name>  ", 0x0F);
            readStr(bufStr, bufSize);
            ASSERT(strlength(bufStr) < MAX_FNAME_LEN);
            cat(finddir_fs(fs_root, bufStr));
        }
        else if(strEql(bufStr,"execute")) { execute(); }
        else if(strEql(bufStr,"switch"))
        {
            	print("\nThe specified directory was not found ", 0x0F);
        }
    	else if(strEql(bufStr,"writer")) { writer(); }
    	else if(strEql(bufStr, "writer -h")) { writerHelp(); }

    	else if(strEql(bufStr, "calc")){ calc(arguments[0]); }
        //else if(strEql(bufStr, "calc -h")){ calcHelp(); }
        else if(strEql(bufStr, "clear"))
        {
           	 clearScreen();
           	 cursorX = 0;
           	 cursorY = 0;
           	 updateCursor();
        }
        else if(strEql(bufStr, "clear -i"))
        {
            	clearScreen();
            	printIntro();
        }
        else if(strEql(bufStr, "newdir"))
        {
            	print("\nReserved", 0x0F);
        }
        else if(strEql(bufStr, "erase"))
        {
            	print("\nReserved", 0x0F);
        }
        else
        {
		print("\n", 0x0F);
		print(bufStr, 0x0F);
            	print(": Command Not Found ", 0x0F);
        }
        newline();
    }
}
