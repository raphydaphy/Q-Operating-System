#include "kheap.h"

extern uint32 end;
uint32 placement_address = (uint32) &end;

uint32 kmalloc_int(uint32 sz, int align, uint32 *phys)
{
    // This will eventually call malloc() on the kernel heap.
    // For now, though, we just assign memory at placement_address
    // and increment it by sz. Even when we've coded our kernel
    // heap, this will be useful for use before the heap is initialised.
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uint32 tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint32 kmalloc_a(uint32 sz)
{
    return kmalloc_int(sz, 1, 0);
}

uint32 kmalloc_p(uint32 sz, uint32 *phys)
{
    return kmalloc_int(sz, 0, phys);
}

uint32 kmalloc_ap(uint32 sz, uint32 *phys)
{
    return kmalloc_int(sz, 1, phys);
}

uint32 kmalloc(uint32 sz)
{
    return kmalloc_int(sz, 0, 0);
}

