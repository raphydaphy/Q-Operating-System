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
bool birthYearValid;

string birthDate;
bool birthDateValid;

string birthMonth;
bool birthMonthValid;

string continent;
bool continentValid;

string country;
bool countryValid;

string state;
bool stateValid;

string city;
bool cityValid;

string zip;
bool zipValid;

void me(string args);

#endif
