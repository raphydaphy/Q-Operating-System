// timer.h -- Defines the interface for all PIT-related functions.
//            Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "isr.h"
#include "screenUtils.h"

void init_timer(uint32 frequency);

#endif
