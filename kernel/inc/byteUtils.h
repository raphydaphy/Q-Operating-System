#ifndef BYTEUTILS_H
#define BYTEUTILS_H

#include "intTypeDefs.h"

void* memcpy(void*, const void*, uint32);
void* memset(void*, char, uint32);
uint16* memsetw(uint16*, uint16, uint32);

#endif
