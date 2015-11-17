#include "intTypeDefs.h"

uint32 kmalloc_a(uint32); // Aligned
uint32 kmalloc_p(uint32, uint32*); // Phys Addr
uint32 kmalloc_ap(uint32, uint32*); // Aligned + Addr
uint32 kmalloc(uint32); // Vanilla

