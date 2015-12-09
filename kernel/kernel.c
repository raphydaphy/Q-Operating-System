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
#include "inc/consoleUI.h"
#include "inc/math.h"
#include "inc/list.h"

#include "apps/me/actparse.h"

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

list_t l = parse("{ intrusion2, entrance,@ (entrance by force or without permission or welcome) }");
for (uint32 i = 0; i < l.size; i++) {
    println(list_get(l, i), 0x0F);
}
l = parse("{ [ attainment, verb.social:attain,+ ] accomplishment,@ (the act of achieving an aim; \"the attainment of independence\") }");
for (uint32 i = 0; i < l.size; i++) {
    println(list_get(l, i), 0x0F);
}
list_destroy(&l);

// This line make the screen red
//paintScreen(0x44);
//printAt("Hello\r\nHello", 0x08, 4, 4);
//drawFrame(0x08, 4, 4, 8, 8);
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
