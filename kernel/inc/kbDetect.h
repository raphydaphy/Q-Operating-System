#ifndef KBDETECT_H
#define KBDETECT_H

#include "error.h"
#include "screenUtils.h"

#define COMMAND_HELP "\nWorking Commands in Q OS: \nwriter\nclear\nexecute\nhi\nskip\nfiles\ncat"
#define PRO_TIP "\nTip: If enter key does not work, it might mean that the input is too long\n"

void readStr(string, uint32);

#endif
