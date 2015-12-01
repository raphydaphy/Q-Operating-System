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
int birthYearInt;

string birthDate;
int birthDateInt;

string birthMonth;

string continent;
string country;
string state;
string city;
string zip;

// define the main Me funciton that does all the data handling for Me
void me(string args);

#endif
