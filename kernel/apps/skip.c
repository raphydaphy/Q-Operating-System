#include "skip.h"

string get0Arg(string rawArgs)
{
    bool zeroArgGenOver = false;
    string curArg = (string) kmalloc(10 * sizeof(char));
    string zeroArg = rawArgs;

    uint16 tmp = 0;
    uint16 modTmp = (tmp + 1);
    while (!zeroArgGenOver && modTmp < arrLength(rawArgs))
    {
        modTmp = tmp + 1;

        // For Debug:
        //printint(tmp,0x03);
        
        char curArgChar = rawArgs[tmp];
        char curArgCharString[] = { curArgChar, '\0' };

        if (streql(curArgCharString," "))
        {
            zeroArgGenOver = true;
            memset(curArg, '\0', 128);
            zeroArg = curArg;
            kfree(curArg);
            return zeroArg;
        }
        else
        {
            print(curArgCharString,0x0F);
            strcat(curArg,curArgCharString);
        }

        tmp++;
    }

    kfree(curArg);
    return zeroArg;
}

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
