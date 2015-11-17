#include "inc/timer.h"
#include "inc/paging.h"
#include "inc/kbDetect.h"
#include "inc/descriptorTables.h"

void launchShell();

int kmain()
{
    init_descriptor_tables();
    clearScreen();
    asm volatile("sti");
    initialize_paging();
    
    print("================================================================================", 0x3F);
    print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);

    launchShell();
    return 0;
}

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

    //allocate some memory for command string buffer. 1kB should be enough for now
    const int bufSize = 128;
    const int editorBufSide = 1024;
    char bufStr[bufSize];
    char writerContents[editorBufSide];
    writerContents[0] = 0;
    
    while (true)
    {
        print("\nQ-Kernel>  ", 0x08);
        typingCmd = true;
        newCmd = true;
        readStr(bufStr, bufSize);
        typingCmd = false;
        
        if(strEql(bufStr, "help"))
        {
            print("\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip", 0x0F);
        }
        else if(strEql(bufStr, "skip"))
        {
            // It literally does nothing... (Useful at callback) 
        }
        else if(strEql(bufStr, "hi"))
        {
            print("\nHello!", 0x3F);
        }
        else if(strEql(bufStr,"execute"))
        {
            print("\n>  ", 0x0F);
            readStr(bufStr, bufSize);
            if(strEql(bufStr,"repeat"))
            {
	            print("\nrepeat>  ", 0x0F);
	            readStr(bufStr, bufSize);
	            writing = 1;
	            while(true)
	            {
	                printch('\n', 0x0F);
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
	            print("The 'do' command does not support the command you entered or it does not exist ", 0x0F);
            }
        }
        else if(strEql(bufStr,"list"))
        {
            print("\nNo Files Found on Disk ", 0x0F);
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
            readStr(writerContents, bufSize);
            writing = false;
        }
        else if(strEql(bufStr,"clear"))
        {
            clearScreen();
            cursorX = 0;
            cursorY = 0;
            updateCursor();
        }
        else if(strEql(bufStr,"clear -i"))
        {
            clearScreen();
            print("================================================================================", 0x3F);
            print("                             Welcome to Q OS                                    ", 0x3F);
            print("================================================================================", 0x3F);
        }
        else if(strEql(bufStr,"newdir"))
        {
            print("\n",0x0F);
        }
        else if(strEql(bufStr,"erase"))
        {
            print("\n",0x0F);
        }
        else
        {
            print("\nCommand Not Found ",0x0F);
        }
        print("\n",0x0F);
    }
}
