#ifndef KERNELFUNCTIONS_H
#define KERNELFUNCTIONS_H

#include "../multiboot.h"
#include "kernelFunctions.h"
#include "fs.h"
#include "timer.h"
#include "error.h"
#include "paging.h"
#include "initrd.h"
#include "kbDetect.h"
#include "descriptorTables.h"
#include "assemblyFunctions.h"

void printIntro();
void launchShell();

#endif
