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

void halt()
{
    loop:
    __asm__ __volatile__ ("hlt");
    goto loop;
}

void reboot()
{
    uint8 good = 0x02;
    while (good & 0x02)
        good = inportb(0x64);
    outportb(0x64, 0xFE);
    halt();
}
