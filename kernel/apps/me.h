#ifndef ME_H
#define ME_H

// Q Libraries
#include "../inc/kheap.h"
#include "../inc/kbDetect.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

// Q System Tools
#include "cat.h"

// Me Libraries
#include "me/sort.h"
#include "me/answer.h"

// define a boolean to see if the setup process is completed
bool hasSetup;

// define all variables to store user data
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

int zipInt;

// define all variables for setup data
bool birthYearValid;
bool birthDateValid;
bool birthMonthValid;

bool continentValid;
bool countryValid;
bool stateValid;
bool cityValid;
bool zipValid;

// define the main Me funciton that does all the data handling for Me
void me(string args);


#endif
