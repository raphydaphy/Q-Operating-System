#include "multiboot.h"

// Q Libraries
#include "inc/kernelFunctions.h"
#include "inc/fs.h"
#include "inc/timer.h"
#include "inc/error.h"
#include "inc/paging.h"
#include "inc/initrd.h"
#include "inc/kbDetect.h"
#include "inc/descriptorTables.h"
#include "inc/assemblyFunctions.h"

// Q Applications
#include "apps/calc.h"
#include "apps/writer.h"
#include "apps/execute.h"

extern uint32 placement_address;

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nreboot\ncalc"
#define PRO_TIP "\nTip: If enter key does not work, it might mean that the input is too long"


void launchShell();
uint32 findInitrd(struct multiboot*);

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
