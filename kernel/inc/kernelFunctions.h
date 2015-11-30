#ifndef KERNELFUNCTIONS_H
#define KERNELFUNCTIONS_H

#include "../multiboot.h"
#include "fs.h"
#include "timer.h"
#include "error.h"
#include "paging.h"
#include "initrd.h"
#include "kbDetect.h"
#include "descriptorTables.h"
#include "assemblyFunctions.h"

// Q Applications
#include "../apps/execute.h"
#include "../apps/calc.h"
#include "../apps/writer.h"
#include "../apps/cat.h"
#include "../apps/files.h"
#include "../apps/system.h"
#include "../apps/skip.h"
#include "../apps/me.h"

void printIntro();

void launchShell();

#endif
