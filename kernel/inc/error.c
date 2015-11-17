#include "error.h"

extern void panic(const string message, const string file, uint32 line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    print("PANIC(", 0x0F);
    print(message, 0x0F);
    print(") at ", 0x0F);
    print(file, 0x0F);
    print(":", 0x0F);
    printint(line, 0x0F);
    print("\n", 0x0F);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const string file, uint32 line, const string desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    print("ASSERTION-FAILED(", 0x0F);
    print(desc, 0x0F);
    print(") at ", 0x0F);
    print(file, 0x0F);
    print(":", 0x0F);
    printint(line, 0x0F);
    print("\n", 0x0F);
    // Halt by going into an infinite loop.
    for(;;);
}

