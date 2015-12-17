#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "charUtils.h"
#include "screenUtils.h"

#define KC_MAGIC_VAL 257

char retCorrespChar(char, char);

string readpasswd();

string readstr();

char getch();

int16 getKeycode();

void initialize_keyboard();

#endif
