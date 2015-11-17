#include "inc/timer.h"
#include "inc/paging.h"
#include "inc/kbDetect.h"
#include "inc/descriptorTables.h"

void launchShell();

int kmain()
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    clearScreen();
    asm volatile("sti");
    initialize_paging();
    print("Hello, paging!\n", 0x0F);

    uint32* ptr = (uint32*) 0xA0000000;
    uint32 do_page_fault = *ptr;

    return 0;
}

/*
int kmain()
{
    init_descriptor_tables();
    clearScreen();
    asm volatile("sti");
    initialize_paging();
    
    layout = 1;
    print("================================================================================", 0x3F);
    print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);
    layout = 0;

    launchShell();
    return 0;
}
*/

void launchShell() {
    print("\nKeybindings in Q OS:", 0x0F);
    print("\n\tCtrl-b -> left", 0x0F);
    print("\n\tCtrl-f -> right", 0x0F);
    print("\n\tCtrl-a -> home", 0x0F);
    print("\n\tCtrl-p -> up", 0x0F);
    print("\n\tCtrl-n -> down", 0x0F);
    print("\n\tCtrl-z -> quit", 0x0F);
    print("\n\tCtrl-l -> clear", 0x0F);
    print("\n", 0x0F);

    while (1)
    {
        layout = 1;
        print("\nQ-Kernel>  ", 0x08);
        layout = 0;
        typingCmd = 1;
        newCmd = 1;
        string ch = readStr();
        typingCmd = 0;
        layout = 1;
        if(strEql(ch, "help"))
        {
            print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip", 0x0F);
        }
        else if(strEql(ch, "skip"))
        {
            // It literally does nothing... (Useful at callback) 
        }
        else if(strEql(ch, "hi"))
        {
            print("\nHello!", 0x3F);
        }
        else if(strEql(ch,"execute"))
        {
            print("\n>  ", 0x0F);
            string tmp = readStr();
            if(strEql(tmp,"repeat"))
            {
	            print("\nrepeat>  ", 0x0F);
	            string tmp = readStr();
	            writing = 1;
	            while(1)
	            {
	                printch('\n', 0x0F);
	                print(tmp, 0x0F);
	            }
            }
            if(strEql(tmp,"c"))
            {
	            print("\nc>  ",0x0F);
	            string c = readStr();
            }
            else
            {
	            print("The 'do' command does not support the command you entered or it does not exist ", 0x0F);
            }
        }
        else if(strEql(ch,"list"))
        {
            print("\nNo Files Found on Disk ", 0x0F);
        }
        else if(strEql(ch,"switch"))
        {
            print("\nThe specified directory was not found ", 0x0F);
        }
        else if(strEql(ch,"writer"))
        {
            layout = 1;
            clearScreen();
            print("================================================================================", 0x3F);
            print("                      Q OS Text Editor Version 0.2                              ", 0x3F);
            print("================================================================================", 0x3F);
            writing = 1;
            layout = 0;
            print(writerContents, 0x0F);
            string writerContents = readStr();
        }
        else if(strEql(ch,"clear"))
        {
            clearScreen();
            cursorX = 0;
            cursorY = 0;
            updateCursor();
        }
        else if(strEql(ch,"clear -i"))
        {
            layout = 1;
            clearScreen();
            print("================================================================================", 0x3F);
            print("                             Welcome to Q OS                                    ", 0x3F);
            print("================================================================================", 0x3F);
            layout = 0;
        }
        else if(strEql(ch,"newdir"))
        {
            print("\n",0x0F);
        }
        else if(strEql(ch,"erase"))
        {
            print("\n",0x0F);
        }
        else
        {
            print("\nCommand Not Found ",0x0F);
        }
        print("\n",0x0F);
        layout = 0;
    }
}
