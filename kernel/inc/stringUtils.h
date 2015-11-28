#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "intTypeDefs.h"

uint16 strlength(string);

bool strEql(string, string);

uint8 strcmp(string, string);

string strcpy(string, string);

string strcat(string, string);

string strTrim(string);

bool isspace(char);

bool isnum(char);

string itos(int);

int ctoi(char);

int stoi(string);

double stod(string);

#endif
