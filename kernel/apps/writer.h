#ifndef WRITER_H
#define WRITER_H

#include "../inc/intTypeDefs.h"

#ifndef WRITERSIZE
#define WRITERSIZE 1024
#endif

// create character holders for the writer program
char writerContents[WRITERSIZE];

// writerHelp() function is ran when a user enters "writer -h"
void writerHelp();

// define the writer() function which is used when somone enters "writer" on the Q Kernel Command line
void writer(string);

#endif
