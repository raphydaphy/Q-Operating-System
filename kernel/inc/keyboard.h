#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "screenUtils.h"

string readpasswd();

string readstr();

char getch();

uint8 getKeycode();

void initialize_keyboard();

#endif
