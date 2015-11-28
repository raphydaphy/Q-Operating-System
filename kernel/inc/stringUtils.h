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

#define itos2(i) itos(i, 2)
#define itos8(i) itos(i, 8)
#define itos10(i) itos(i, 10)
#define itos16(i) itos(i, 16)
#define itos36(i) itos(i, 36)
string itos(int, uint8);

int stoi(string);

double stod(string);

#endif
