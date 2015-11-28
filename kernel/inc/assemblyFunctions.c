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
}
