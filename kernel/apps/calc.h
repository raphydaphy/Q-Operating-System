#ifndef CALC_H
#define CALC_H

#include "../inc/math.h"
#include "../inc/kbDetect.h"
#include "../inc/byteUtils.h"
#include "../inc/charUtils.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

#ifndef CALCSIZE
#define CALCSIZE 128
#endif

// math storage variables
char calcInput[CALCSIZE + 2]; // For `+0`
int mathOp[CALCSIZE];
int tempNum;
double strNum[CALCSIZE];
int strNumCount;

// contatination function for the calculator app
int concat(int, int);

// main calc() function to run from kernel.c
void calc(string);

// calcHelp() function for when users run "calc -h"
void calcHelp();

// mathError() function to print an error message
void mathError(uint8);

#endif
