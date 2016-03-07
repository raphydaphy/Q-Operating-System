//Here we have ASM based functions in C that control port managment for Q OS

#ifndef ASSEMBLYFUNCTIONS_H
#define ASSEMBLYFUNCTIONS_H

#include "intTypeDefs.h"

uint8 inportb (uint16);

void outportb (uint16, uint8);

void outportw(uint16, uint16);

uint16 IoRead16(uint16 _port);

void IoWrite32(uint16 _port, uint32 _data);

uint32 IoRead32(uint16 _port);

// void io_wait();

void halt();

void reboot();

void shutdown();

extern void asm_powoff();

#endif
