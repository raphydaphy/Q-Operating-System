#ifndef ME_H
#define ME_H

#include "../inc/kbDetect.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

// An array to store each word that you enter
char *words[9];

// Variables for each word you enter
string word1;
string word2;
string word3;
string word4;
string word5;
string word6;
string word7;
string word8;
string word9;
string word10;


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

// random counter integers needed in various parts of me.c
//int tmp;

void me(string args);

#endif
