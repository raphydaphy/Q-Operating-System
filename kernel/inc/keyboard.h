#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "list.h"
#include "screenUtils.h"
#include "strbuilder.h"

string readstr();

char getch();

void initialize_keyboard();

#endif
