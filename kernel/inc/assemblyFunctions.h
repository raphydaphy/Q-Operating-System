//Here we have ASM based functions in C that control port managment for Q OS

#ifndef ASSEMBLYFUNCTIONS_H
#define ASSEMBLYFUNCTIONS_H

#include "intTypeDefs.h"

uint8 inportb (uint16);

void outportb (uint16, uint8);

void outportw(uint16, uint16);

void halt();

void reboot();

void shutdown();

#endif
