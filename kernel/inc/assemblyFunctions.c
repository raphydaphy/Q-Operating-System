#include "assemblyFunctions.h"

uint8 inportb (uint16 _port)
{
	uint8 rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16 _port, uint8 _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void outportw(uint16 _port, uint16 _data)
{
	__asm__ __volatile__ ("outw %1, %0" : : "dN" (_port), "a" (_data));
}

void halt()
{
    loop:
    __asm__ __volatile__ ("hlt");
    goto loop;
}

void reboot()
{
    uint8 rebootTemp = 0x02;
    while (rebootTemp & 0x02)
        rebootTemp = inportb(0x64);
    outportb(0x64, 0xFE);
    halt();
}

void shutdown()
{
/* OLD SHUTDOWN SEQUENCE. does not work on some VM
    __asm__ __volatile__ ("cli");
		while(true) {
        //Shutdown Qemu and bochs
        outportw(0xB004, 0x2000);

        //shutdown code for Qemu and bochs
        for (const char *s = "Shutdown"; *s; ++s){
            outportb(0x8900, *s);
        }
        __asm__ __volatile__ ("cli; hlt");
    }
*/
	//New shutdown sequence. More info here: http://stackoverflow.com/questions/21463908/x86-instructions-to-power-off-computer-in-real-mode
	//Tested, returns an unhanded interrupt: 13 with unlimited loop
	/*__asm__ __volatile__(
		"cli\n"

		"movb 0x53, %ah\n"
		"xorw %bx,%bx\n"
		"int $0x15\n"

		"movb 0x53, %ah\n"
		"xorw %bx,%bx\n"
		"movb $0x82,%cl\n"
		"int $0x15\n"

		"movb $0x53,%al\n"
		"movw $0x8001,%bx\n"
		"movw $0x8003,%cx\n"
		"int $0x15\n"

		"ret\n"
	);*/

	//Tested, returns an unhanded interrupt: 13 with unlimited loop
        /*__asm__ __volatile__(
                "mov %ax, 0x1000\n"
                "mov %ax, %ss\n"
                "mov %sp, 0xf000\n"
                "mov %ax, 0x5307\n"
                "mov %bx, 0x8001\n"
                "mov %cx, 0x8003\n"
                "int $0x15\n"
	);*/
}
