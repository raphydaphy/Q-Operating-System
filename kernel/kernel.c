#include "multiboot.h"

#include "inc/fs.h"
#include "inc/timer.h"
#include "inc/error.h"
#include "inc/paging.h"
#include "inc/initrd.h"
#include "inc/kbDetect.h"
#include "inc/descriptorTables.h"
#include "inc/assemblyFunctions.h"

extern uint32 placement_address;

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc"
#define PRO_TIP "\nTip: If enter key does not work, it might mean that the input is too long"

void listTree();
void launchShell();
void catFile(fs_node_t*);
uint32 findInitrd(struct multiboot*);

void printIntro(){
    print("================================================================================", 0x3F);
    print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);
}

int kmain(struct multiboot* mboot_ptr)
{
    clearScreen();
    init_descriptor_tables();
    __asm__ __volatile__("sti");

    uint32 initrd_location = findInitrd(mboot_ptr);
    initialize_paging();

    // Initialize the initial ramdisk, and set it as the filesystem root.
    fs_root = initialize_initrd(initrd_location);

    printIntro();

    println(PRO_TIP, 0x0F);
    kbHelp();

    launchShell();
    return 0;
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

//Concatinating for calculator
int concat(int x, int y){
    int pow = 10;
    while(y >= pow)
        pow*= 10;
    return x * pow + y;
}

uint32 findInitrd(struct multiboot* mboot_ptr)
{
    // Find the location of our initial ramdisk.
    ASSERT(mboot_ptr->mods_count > 0);
    uint32 initrd_location = *((uint32*)mboot_ptr->mods_addr);
    uint32 initrd_end = *(uint32*)(mboot_ptr->mods_addr+4);
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;
    return initrd_location;
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
    const int editorBufSize = 1024;
    char bufStr[bufSize];

    //Character holder for writer program
    char writerContents[editorBufSize];
    writerContents[0] = 0;

    //Math storage for calculator program
    char calcInput[bufSize];
    calcInput[0] = 0;
    int mathOp = 0;
    int tempNum = 0;
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
            print("\ntype>  ", 0x0F);
            readStr(bufStr, bufSize);
            if(strEql(bufStr,"repeat"))
            {
	            print("\nrepeat>  ", 0x0F);
	            readStr(bufStr, bufSize);
	            writing = 1;
	            while(true)
	            {
                    newline();
	                print(bufStr, 0x0F);
	            }
            } 
            else if(strEql(bufStr,"c"))
            {
	            print("\nc>  ",0x0F);
	            readStr(bufStr, bufSize);
            }
            else
            {
	            print("\nThe 'execute' command does not support the command you entered or it does not exist ", 0x0F);
            }
        }
        else if(strEql(bufStr,"switch"))
        {
            print("\nThe specified directory was not found ", 0x0F);
        }
        else if(strEql(bufStr,"writer"))
        {
            clearScreen();
            print("================================================================================", 0x3F);
            print("                      Q OS Text Editor Version 0.2                              ", 0x3F);
            print("================================================================================", 0x3F);
            writing = true;
            readStr(writerContents, editorBufSize);
            writing = false;
        }
        //Calculator program
	else if(strEql(bufStr, "calc")){
            print("\nUse calc -h for help", 0x0F);
	    print("\n>  ", 0x0F);
            readStr(calcInput, editorBufSize);
	    for(int i = 0; i < bufSize; i++){
	        if(calcInput[i] == 0 || calcInput[i] == 10)
                    break;
                else{
		        switch (calcInput[i]){
		            case 48://Number 0
		             tempNum = concat(0, tempNum);
		            break;
		            case 49://Number 1
		             tempNum = concat(1, tempNum);
		            break;
		            case 50://Number 2
		             tempNum = concat(2, tempNum);
		            break;
		            case 51://Number 3
		             tempNum = concat(3, tempNum);
		            break;
		            case 52://Number 4
		             tempNum = concat(4, tempNum);
		            break;
		            case 53://Number 5
		             tempNum = concat(5, tempNum);
		            break;
		            case 54://Number 6
		             tempNum = concat(6, tempNum);
		            break;
		            case 55://Number 7
		             tempNum = concat(7, tempNum);
		            break;
		            case 56://Number 8
		             tempNum = concat(8, tempNum);
		            break;
		            case 57://Number 9
		             tempNum = concat(9, tempNum);
		            break;
		            default:
				mathOp = calcInput[i]; //Treat everything else as a math operator (should do for now)
		            break;
		        }
	        }
            }
	    printint(tempNum, 0x0F);
	}
        //Calculator program help
        else if(strEql(bufStr, "calc -h")){
	    print("\nCalculator help: ", 0x0F);
            print("\n[HELP TEXT HERE]", 0x0F);
	}
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
