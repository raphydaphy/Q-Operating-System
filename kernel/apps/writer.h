#ifndef WRITER_H
#define WRITER_H

#ifndef WRITERSIZE
#define WRITERSIZE 1024
#endif

// create character holders for the writer program
char writerContents[WRITERSIZE];

// define the writer() function which is used when somone enters "writer" on the Q Kernel Command line
void writer();

// writerHelp() function is ran when a user enters "writer -h"
void writerHelp();

#endif
