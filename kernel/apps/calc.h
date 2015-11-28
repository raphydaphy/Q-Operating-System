#ifndef CALC_H
#define CALC_H

#include "../inc/charUtils.h"
#include "../inc/intTypeDefs.h"

#ifndef CALCSIZE
#define CALCSIZE 128
#endif

// math storage variables
char calcInput[CALCSIZE];
int mathOp[CALCSIZE];
int tempNum;
double strNum[CALCSIZE];
int strNumCount;

// contatination function for the calculator app
int concat(int x, int y);

// main calc() function to run from kernel.c
void calc(string);

// calcHelp() function for when users run "calc -h"
void calcHelp();

// mathError() function to print an error message
void mathError();
#endif
