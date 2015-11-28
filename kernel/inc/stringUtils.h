#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "charUtils.h"
#include "intTypeDefs.h"

uint16 strlength(string);

bool strEql(string, string);

uint8 strcmp(string, string);

string strcpy(string, string);

string strcat(string, string);

string strTrim(string);

string itos(int);

int stoi(string);

double stod(string);

#endif
