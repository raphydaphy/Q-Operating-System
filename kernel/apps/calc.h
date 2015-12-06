#ifndef CALC_H
#define CALC_H

#include "../inc/math.h"
#include "../inc/list.h"
#include "../inc/kbDetect.h"
#include "../inc/byteUtils.h"
#include "../inc/charUtils.h"
#include "../inc/strbuilder.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

typedef enum {
    START_W_OP,
    DIV_BY_ZERO,
    ILLEGAL_OP,
    OTHER
} mathExcept;

// Initializes the variable map! IMPORTANT!
void initialize_calc();

// main calc() function to run from kernel.c
void calc(string);

// calcHelp() function for when users run "calc -h"
void calcHelp();

// mathError() function to print an error message
void mathError(mathExcept);

float calc_parse(strbuilder_t);

float evaluate(list_t);

#endif
