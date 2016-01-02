#ifndef EXECUTE_H
#define EXECUTE_H

#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"
#include "../inc/kheap.h"

#include "calc.h"

#ifndef EXECUTESIZE
#define EXECUTESIZE 1024
#endif

// create input holders for the execute program
char executeContents[EXECUTESIZE];

// declare the main execute() function for when "execute" is written into the command line
void execute(string);

#endif
