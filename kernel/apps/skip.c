#include "skip.h"

void skip(string args) {
    newline();

    // this is used for the while statement below and when it is false the while statement will stop running
    bool skippingStuff = true;

    // this is here to emulate the offset value in the answer.c file
    int offset = 0;

    while (skippingStuff)
    {
        print("\n Enter Something>  ",0xF8);
        readStr(args,128);

        if((!streql(splitArg(args,1),"") && offset == 0) || !streql(splitArg(args,2),""))
        {
            print("\n Multiple Words Detected!",0xF0);
            print("\n First Letter of Args: ",0x0D);

            //char zeroValue = args[0];
            //char* newArgs[] = { zeroValue, '\0' };
            //print(newArgs,0x0F);

            //print("\nConcatinated Argument #0: ",0xF0);
            //strcat(newArgs,splitArg(args,0));
            //print(newArgs,0x0D);
        }
        else if (streql(splitArg(args,0),"exit"))
        {
            skippingStuff = false;
        }

        print("\n Full Args: ",0xF8);
        print(args,0xDB);

        print("\nArgument #0: ",0xF8);
        print(splitArg(args,0),0xDB);

        print("\nArgument #1: ",0xF8);
        print(splitArg(args,1),0xDB);

        print("\nArgument #2: ",0xF8);
        print(splitArg(args,2),0xDB);

        print("\nArgument #3: ",0xF8);
        print(splitArg(args,3),0xDB);
    }
}
