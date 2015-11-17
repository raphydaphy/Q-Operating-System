#include "multiboot.h"

#include "inc/fs.h"
#include "inc/timer.h"
#include "inc/error.h"
#include "inc/paging.h"
#include "inc/initrd.h"
#include "inc/kbDetect.h"
#include "inc/descriptorTables.h"

extern uint32 placement_address;

void catFile(fs_node_t*);
void listTree();
void launchShell();
uint32 findInitrd(struct multiboot*);

int kmain(struct multiboot* mboot_ptr)
{
    clearScreen();
    init_descriptor_tables();
    asm volatile("sti");

    uint32 initrd_location = findInitrd(mboot_ptr);
    initialize_paging();

    // Initialize the initial ramdisk, and set it as the filesystem root.
    fs_root = initialize_initrd(initrd_location);

    layout = 1;
    print("================================================================================", 0x3F);
    print("                             Welcome to Q OS                                    ", 0x3F);
    print("================================================================================", 0x3F);
    layout = 0;

    launchShell();
    return 0;
}

#define RBUFF 256
void catFile(fs_node_t* fsnode)
{
    printch('\n', 0x0F);
    if ((fsnode->flags & 0x7) == FS_FILE)
    {
        char buf[RBUFF];
        uint32 sz = read_fs(fsnode, 0, RBUFF, buf);
        int j;
        for (j = 0; j < sz; j++)
            printch(buf[j], 0x0F);
        printch('\n', 0x0F);
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
        printch('\n', 0x0F);
        i++;
    }
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
    print("\n\tCtrl-l -> clear", 0x0F);
    print("\n", 0x0F);
}

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat"

void launchShell() {
    kbHelp();
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
        if (strEql(strTrim(ch), ""))
        {
            print(COMMAND_HELP, 0x0F);
        }
        else if(strEql(ch, "help"))
        {
            kbHelp();
            print(COMMAND_HELP, 0x0F);
        }
        else if(strEql(ch, "skip"))
        {
            // It literally does nothing... (Useful at callback) 
        }
        else if(strEql(ch, "hi"))
        {
            print("\nHello!", 0x3F);
        }
        else if(strEql(ch, "files"))
        {
            print("\n", 0x0F);
            listTree();
        }
        else if(strEql(ch, "cat"))
        {
            print("\nFile Name>  ", 0x0F);
            string tmp = readStr();
            ASSERT(strlength(tmp) < MAX_FNAME_LEN);
            catFile(finddir_fs(fs_root, tmp));
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
