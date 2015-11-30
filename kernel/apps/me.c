#include "me.h"

bool hasSetup = false;

void me(string args) {

    if (strEql(splitArg(args, 1), "setup") || !hasSetup)
    {
        if (strEql(splitArg(args, 2), "skipper") && !hasSetup)
        {
            hasSetup = true;
            print("\nYou have skipped the Me setup process, some answers may be strange :D",0x06);
        }
        else if (!hasSetup)
        {
            print("\nWelcome to Me.",0x03);
            print("\nMe is the worlds first truly rubbish personal assistant.",0x03);
            print("\nTo use me, simply ask it a question.",0x03);
            print("\nFor example, type 'me what is the time?'",0x03);
            print("\nTo start using Me, please enter some basic information below when prompted.",0x03);
            newline();

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

            newline();
            hasSetup = "true";
            print("Me is now ready to use!",0x03);

            newline();
            print("When Me dosen't know information, it can ask you for help.",0x03);
        }
        else
        {
            print("\nYou have already completed the setup process for Me!",0x05);
        }
    }
    else
    {
        // split args into an array of words
        words[0] = splitArg(args, 1);
        words[1] = splitArg(args, 2);
        words[2] = splitArg(args, 3);
        words[3] = splitArg(args, 4);
        words[4] = splitArg(args, 5);
        words[5] = splitArg(args, 6);
        words[6] = splitArg(args, 7);
        words[7] = splitArg(args, 8);
        words[8] = splitArg(args, 9);
        words[9] = splitArg(args, 10);

        // make seperate strings for each word
        word1 = splitArg(args, 1);
        word2 = splitArg(args, 2);
        word3 = splitArg(args, 3);
        word4 = splitArg(args, 4);
        word5 = splitArg(args, 5);
        word6 = splitArg(args, 6);
        word7 = splitArg(args, 7);
        word8 = splitArg(args, 8);
        word9 = splitArg(args, 9);
        word10 = splitArg(args, 10);

        // make a special array for testing
        char *tests[] = {
           "Thing",
           "Another",
           "Thing"
       };
        // print out each item in the words[] array

        for(int tmp = 0; tmp < 10; tmp++)
        {
            newline();
            printint(tmp,0x09);
            print(" : ",0x08);
            print(words[tmp],0x09);
        }

        for(int tmp = 0; tmp < 10; tmp++)
        {
            newline();
            printint(tmp,0x0A);
            print(" : ",0x0B);
            print(tests[tmp],0x0A);
        }

        newline();
        print(word1,0x0B);
        newline();
        print(word2,0x0B);
        newline();
        print(word3,0x0B);
        newline();
        print(word4,0x0B);
        newline();
        print(word5,0x0B);
        newline();
        print(word6,0x0B);
        newline();
        print(word7,0x0B);
        newline();
        print(word8,0x0B);
        newline();
        print(word9,0x0B);
        newline();
        print(word10,0x0B);

        newline();
        print(splitArg(args, 1),0x0C);
        newline();
        print(splitArg(args, 2),0x0C);
        newline();
        print(splitArg(args, 3),0x0C);
        newline();
        print(splitArg(args, 4),0x0C);
        newline();
        print(splitArg(args, 5),0x0C);
        newline();
        print(splitArg(args, 6),0x0C);
        newline();
        print(splitArg(args, 7),0x0C);
        newline();
        print(splitArg(args, 8),0x0C);
        newline();
        print(splitArg(args, 9),0x0C);
        newline();
        print(splitArg(args, 10),0x0C);
    }
}
