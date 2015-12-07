#include "skip.h"



void skip(string args) {
    newline();

    // this is used for the while statement below and when it is false the while statement will stop running
    bool skippingStuff = true;

    while (skippingStuff)
    {
        print("\n Enter Something>  ",0xF8);
        readStr(args,128);

        if (streql(splitArg(args,0),"exit"))
        {
            skippingStuff = false;
        }

        print("\n Full Args: ",0xF8);
        print(args,0xDB);


        print("\nArgument #0: ",0xF8);
        get0Arg(args);

        print("\nArgument #1: ",0xF8);
        print(splitArg(args,1),0xDB);

        print("\nArgument #2: ",0xF8);
        print(splitArg(args,2),0xDB);

        print("\nArgument #3: ",0xF8);
        print(splitArg(args,3),0xDB);
    }
}
