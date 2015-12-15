// timer.h -- Defines the interface for all PIT-related functions.
//            Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "isr.h"
#include "screenUtils.h"

void init_timer(uint32);

void waitTicks(uint32);

void waitSeconds(uint32);

#endif
