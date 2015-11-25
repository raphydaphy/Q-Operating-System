#include "skip.h"

#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"


skip(string args) {
    newline();
    print("You have entered the ",0x03);
    print("skip",0x04);
    print(" command with the",0x03);
    print(args,0x04);
    print(" argument.",0x03);
}
