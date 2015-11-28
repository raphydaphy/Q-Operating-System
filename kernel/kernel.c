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
#include "inc/math.h"

extern uint32 placement_address;

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip (the no action)\nfiles\ncat\nsystem\ncalc"
#define PRO_TIP "\nTip: If enter key does not work, it might mean that the input is too long"

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
