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

void catFile(fs_node_t* fsnode)
{
    newline();
    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        const uint32 rbuff = fsnode->length;
        char buf[rbuff];
        uint32 sz = read_fs(fsnode, 0, rbuff, (uint8*) buf);
        uint32 j;
        for (j = 0; j < sz; j++)
            printch(buf[j], 0x0F);
        newline();
    }
}

void listTree() {
    // list the contents of
    int i = 0;
    struct dirent *node = 0;
    while ((node = readdir_fs(fs_root, i)) != 0)
    {
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);

        if ((fsnode->flags & 0x7) == FS_DIRECTORY)
        {
            print("dir \t", 0x0F);
            print(node->name, 0x0F);
            printch('/', 0x0F);
        }
        else
        {
            print("file\t", 0x0F);
            print(node->name, 0x0F);
        }
        newline();
        i++;
    }
}

void kbHelp()
{
    print("\nKeybindings in Q OS:", 0x0F);
    print("\n\tCtrl-b -> left", 0x0F);
    print("\n\tCtrl-f -> right", 0x0F);
    print("\n\tCtrl-a -> home", 0x0F);
    print("\n\tCtrl-p -> up", 0x0F);
    print("\n\tCtrl-n -> down", 0x0F);
    print("\n\tCtrl-z -> quit", 0x0F);
    println("\n\tCtrl-l -> clear", 0x0F);
}

void launchShell() {
    //allocate some memory for command string buffer. 1kB should be enough for now
    const int bufSize = 128;
    char bufStr[bufSize];

    while (true)
    {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        readStr(bufStr, bufSize);
        typingCmd = false;

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
        else if(strEql(bufStr, "reboot"))
        {
            //reboots the computer
            reboot();
        }
        else if(strEql(bufStr, "skip"))
        {
            // It literally does nothing... (Useful at callback) 
        }
        else if(strEql(bufStr, "hi"))
        {
            print("\nHello!", 0x3F);
        }
        else if(strEql(bufStr, "files"))
        {
            newline();
            listTree();
        }
        else if(strEql(bufStr, "cat"))
        {
            print("\nFile Name>  ", 0x0F);
            readStr(bufStr, bufSize);
            ASSERT(strlength(bufStr) < MAX_FNAME_LEN);
            catFile(finddir_fs(fs_root, bufStr));
        }
        else if(strEql(bufStr,"execute"))
        {
            execute();
        }
        else if(strEql(bufStr,"switch"))
        {
            	print("\nThe specified directory was not found ", 0x0F);
        }
	else if(strEql(bufStr,"writer")) { writer(); }
	else if(strEql(bufStr, "writer -h")) { writerHelp(); }
	
	else if(strEql(bufStr, "calc")){ calc(); }
        else if(strEql(bufStr, "calc -h")){ calcHelp(); }

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
            	print("\nCommand Not Found ", 0x0F);
        }
        newline();
    }
}
