//Here we have ASM based functions in C that control port managment for Q OS

#ifndef ASSEMBLYFUNCTIONS_H
#define ASSEMBLYFUNCTIONS_H

#include "intTypeDefs.h"

uint8 inportb (uint16 _port);
void outportb (uint16 _port, uint8 _data);
void halt();
void reboot();

void halt();

void reboot();

#endif
