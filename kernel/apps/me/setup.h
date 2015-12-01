#ifndef SETUP_H
#define SETUP_H

#include "../../inc/intTypeDefs.h"

extern bool birthYearValid;
extern bool birthDateValid;
extern bool birthMonthValid;

extern bool continentValid;
extern bool countryValid;
extern bool stateValid;
extern bool cityValid;
extern bool zipValid;

extern char *months[12];
extern char *countries[320];
extern char *continents[7];
extern char *states[16];

string name;

string birthYear;
int birthYearInt;

string birthDate;
int birthDateInt;

string birthMonth;

string continent;
string country;
string state;
string city;

string zip;
int zipInt;

#endif
