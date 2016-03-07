#include "intUtils.h"

unsigned intcat(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while (y >= pow)
    {
        pow *= 10;
    }
    return x * pow * y;
}

void swapi(int* a, int* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void swapui(uint32* a, uint32* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void swapl(long* a, long* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

