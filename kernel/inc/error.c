#include "error.h"

extern void panic(const string message, const string file, uint32 line)
{
    // We encountered a massive problem and have to stop.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("PANIC(", 0x9F);
    print(message, 0x9F);
    print(") at ", 0x9F);
    print(file, 0x9F);
    print(":", 0x9F);
    printint(line, 0x9F);
    print("\n", 0x9F);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const string file, uint32 line, const string desc)
{
    // An assertion failed, and we have to panic.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("ASSERTION-FAILED(", 0x9F);
    print(desc, 0x9F);
    print(") at ", 0x9F);
    print(file, 0x9F);
    print(":", 0x9F);
    printint(line, 0x9F);
    print("\n", 0x9F);
    // Halt by going into an infinite loop.
    for(;;);
}
