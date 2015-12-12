#ifndef KBDETECT_H
#define KBDETECT_H

#include "error.h"
#include "screenUtils.h"

const char kbLowerChars[256];

const char kbShiftChars[256];

const char kbCapslchars[256];

void readStr(string, uint32, bool);

void kbHelp();

#endif
