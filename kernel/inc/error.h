#ifndef ERROR_H
#define ERROR_H

#include "screenUtils.h"

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const string message, const string file, uint32 line);
extern void panic_assert(const string file, uint32 line, const string desc);

#endif
