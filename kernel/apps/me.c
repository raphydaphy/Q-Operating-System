#include "me.h"

void me(string args) {
    if (strEql(splitArg(args, 1), "setup"))
    {
        print("Welcome to Me.",0x03);
        print("\nMe is the worlds first truly rubbish personal assistant.",0x03);
        print("\nTo use me, simply ask it a question.",0x03);
        print("\nFor example, type 'me what is the time?'",0x03);
        print("\nTo start using Me, please enter some basic information below when prompted.",0x03);

        newline();
        print("What is your name: ",0x02);
        readStr(name,128);

        newline();
        print("What year were you born in: ",0x02);
        readStr(birthYear,128);

        newline();
        print("What day of the month were you born in: ",0x02);
        readStr(birthDate,128);

        newline();
        print("What month were you born in: ",0x02);
        readStr(birthMonth,128);

        newline();
        print("What continent do you live in: ",0x02);
        readStr(continent,128);

        newline();
        print("What country do you live in: ",0x02);
        readStr(country,128);

        newline();
        print("What state do you currently live in: ",0x02);
        readStr(state,128);

        newline();
        print("What city do you live in: ",0x02);
        readStr(city,128);

        newline();
        print("What is the zip code in your area: ",0x02);
        readStr(zip,128);
    }
    else
    {
        // testing stuff here
        newline();
        print(splitArg(args, 1),0x0F);
        newline();
        print("\n",0x0F);
        print(splitArg(args, 2),0x0F);
    }
}
