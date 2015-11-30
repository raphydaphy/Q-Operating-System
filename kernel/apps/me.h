#ifndef ME_H
#define ME_H

#include "../inc/kbDetect.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

// An array to store each word that you enter
char* words[];

// Some variables to store basic information about our user
string name;

string birthYear;
string birthDate;
string birthMonth;

string continent;
string country;
string state;
string city;
string zip;

void me(string args);

#endif
