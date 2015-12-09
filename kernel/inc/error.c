#include "error.h"

extern void panic(const string message, const string file, uint32 line)
{
    // We encountered a massive problem and have to stop.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("PANIC(", white);
    print(message, white);
    print(") at ", white);
    print(file, white);
    print(":", white);
    printint(line, white);
    print("\n", white);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const string file, uint32 line, const string desc)
{
    // An assertion failed, and we have to panic.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("ASSERTION-FAILED(", white);
    print(desc, white);
    print(") at ", white);
    print(file, white);
    print(":", white);
    printint(line, white);
    print("\n", white);
    // Halt by going into an infinite loop.
    for(;;);
}
