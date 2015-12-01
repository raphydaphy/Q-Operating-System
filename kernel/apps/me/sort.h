#ifndef SORT_H
#define SORT_H

// Q Libraries
#include "../../inc/intTypeDefs.h"
#include "../../inc/stringUtils.h"
#include "../../inc/screenUtils.h"

// Me Data Libraries
#include "noun.h"
#include "verb.h"

// give this function a word and it will potentially tell you what kind of word it is in detail
// for example, "puppy" returns 1.2 which indicates a "noun" about "animals"
// for more information on all the return values for this function have a look at the wiki
// link: https://github.com/raphydaphy/Q-Operating-System/wiki/Me
double sort(char*);

#endif
