#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "screenUtils.h"

uint8 itermVal;

string readpasswd();

string readstr();

char getch();

uint8 getKeycode();

void initialize_keyboard();

#endif
