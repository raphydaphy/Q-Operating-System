#include "me.h"

// Here we declare all the arrays we need for Me runtime
// We should probably move this to another file soon
char *months[] = {
    "January",
    "Febuary",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

// Here we setup all the boolean values that we need for Me
// We should probably move this to another file soon when it gets longer
bool hasSetup = false;

bool birthYearValid;
bool birthDateValid;
bool birthMonthValid = false;

bool continentValid;
bool countryValid;
bool stateValid;
bool cityValid;
bool zipValid;

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

            while (!birthMonthValid)
            {
                newline();
                print("What month were you born in: ",0x02);
                readStr(birthMonth,128);

                for(int tmp = 0; tmp < 11; tmp++)
                {
                    if (strEql(months[tmp],birthMonth))
                    {
                        birthMonthValid = true;
                    }
                }

                if (!birthMonthValid)
                {
                    print("\nThe month you entered appears to be invalid. Please enter the real month you were born in.",0x0C);
                }
            }

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
        for(int tmp = 1; tmp < 10; tmp++)
        {
            newline();
            printint(tmp,0x0A);
            print(" : ",0x0B);
            print(splitArg(args, tmp),0x0A);
        }
    }
}
