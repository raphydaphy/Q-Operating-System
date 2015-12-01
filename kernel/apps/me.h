#ifndef ME_H
#define ME_H

// Q Libraries
#include "../inc/kbDetect.h"
#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"

// Me Libraries
#include "me/setup.h"
#include "me/noun.h"
#include "me/verb.h"
#include "me/sort.h"

// define a boolean to see if the setup process is completed
bool hasSetup;

// define the main Me funciton that does all the data handling for Me
void me(string args);

#endif
