#ifndef SETUP_H
#define SETUP_H

#include "../../inc/intTypeDefs.h"

extern bool hasSetup;

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

#endif
