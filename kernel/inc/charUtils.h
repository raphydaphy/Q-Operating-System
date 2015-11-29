#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include "intTypeDefs.h"

/* Start inline methods */
bool isspace(char);

bool isnum(char);

bool isalpha(char);

bool islower(char);

bool isupper(char);

bool isword(char);
/* End inline methods */

char toLowerC(char);

char toUpperC(char);

int ntoi(char);

int ctoi(char);

char itoc(int);

#endif
