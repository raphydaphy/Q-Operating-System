#ifndef ME_H
#define ME_H

// Q Libraries
#include "../inc/kbDetect.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

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
