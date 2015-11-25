#ifndef CALC_H
#define CALC_H

#include "../inc/intTypeDefs.h"

#ifndef CALCSIZE
#define CALCSIZE 128
#endif

// math storage variables
char calcInput[CALCSIZE];
int mathOp;
int tempNum;
int strNum;
int mathError;

// contatination function for the calculator app
int concat(int x, int y);

// main calc() function to run from kernel.c
void calc(string);

// calcHelp() function for when users run "calc -h"
void calcHelp();

#endif
