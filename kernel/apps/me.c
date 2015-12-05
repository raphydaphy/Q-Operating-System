#include "me.h"

#define curWord toUpper(splitArg(args, tmp))

bool hasSetup = false;
char zip[18];

bool birthYearValid = false;
bool birthDateValid = false;
bool birthMonthValid = false;

bool continentValid = false;
bool countryValid = false;
bool stateValid = false;
bool cityValid = false;
bool zipValid = false;

void me(string args) {
    if (streql(splitArg(args, 1), "setup") || !hasSetup)
    {
        if (streql(splitArg(args, 2), "skip") && !hasSetup)
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
            print("What is your name: ",0x0B);
            readStr(name,128);

            while (!birthYearValid)
            {
                newline();
                print("What year were you born in: ",0x0B);
                readStr(birthYear,5);
                birthYearInt = stoi(birthYear);

                // need to make this always the current year + 1
                if (birthYearInt < 2016 && birthYearInt > 1900)
                {
                    birthYearValid = true;
                    print(" Good",0x02);
                }

                if (!birthYearValid)
                {
                    print(" Invalid",0x0C);
                }
            }


            while (!birthDateValid)
            {
                newline();
                print("What day of the month were you born in: ",0x0B);
                readStr(birthDate,3);
                birthDateInt = stoi(birthDate);

                if (birthDateInt < 32)
                {
                    birthDateValid = true;
                    print(" Good",0x02);
                }

                if (!birthDateValid)
                {
                    print(" Invalid",0x0C);
                }
            }

            while (!birthMonthValid)
            {
                newline();
                print("What month were you born in: ",0x0B);
                readStr(birthMonth,128);
                birthMonth = toUpper(birthMonth);

                if (findInDictionary("me/setup/month.text",birthMonth))
                {
                    birthMonthValid = true;
                    print(" Good",0x02);
                }

                if (!birthMonthValid)
                {
                    print(" Invalid",0x0C);
                }
            }

            while (!continentValid)
            {

                newline();
                print("What continent do you live in: ",0x0B);
                readStr(continent,128);
                continent = toUpper(continent);

                if (findInDictionary("me/setup/continent.text",continent))
                {
                    continentValid = true;
                    print(" Good",0x02);
                }

                if (!continentValid)
                {
                    print(" Invalid",0x0C);
                }
            }


            while (!countryValid)
            {
                newline();
                print("What country do you live in: ",0x0B);
                readStr(country,128);
                country = toUpper(country);

                if (findInDictionary("me/setup/country.text",country))
                {
                    countryValid = true;
                    print(" Good",0x02);
                }

                if (!countryValid)
                {
                    print(" Invalid",0x0C);
                }
            }

            while (!stateValid)
            {
                newline();
                print("What state/province do you currently live in: ",0x0B);
                readStr(state,128);
                state = toUpper(state);

                if (findInDictionary("me/setup/state.text",state))
                {
                    stateValid = true;
                    print(" Good",0x02);
                }

                if (!stateValid)
                {
                    print(" Invalid",0x0C);
                }
            }

            newline();
            print("What city do you live in: ",0x0B);
            readStr(city,128);

            while (!zipValid)
            {
                newline();
                print("What is the zip/post code in your area: ",0x0B);
                readStr(zip, 17);
                zipInt = htoi(zip);
                if (zipInt > 0)
                {
                    zipValid = true;
                    print(" Good",0x02);
                }
            }

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
        bool over = false;
        int tmp = 0;

        newline();

        while (!over)
        {
            tmp++;

            if (streql(splitArg(args, tmp),""))
            {
                over = true;
            }
            else
            {
                print(" | ",0x0A);
                print(toUpper(splitArg(args, tmp)),0x0D);
                print(" ",0x0D);
                print(sort(splitArg(args, tmp)),0x0D);
            }
        }
    }
}
