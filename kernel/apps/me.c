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

bool querying = false;

void me(string args) {
    if (!hasSetup)
    {
        if (streql(splitArg(args, 1), "help")) {
            print("\nMe is here to help you... Believe me...", brown);
        }
        else if (streql(splitArg(args, 1), "test") && !hasSetup)
        {
            hasSetup = true;
            print("\nYou have skipped the Me setup process.",brown);
        }
        else if (!hasSetup)
        {
            print("\nWelcome to Me.",grey);
            print("\nMe is the worlds first truly rubbish personal assistant.",grey);
            print("\nTo use me, simply ask it a question.",grey);
            print("\nFor example, type 'me what is the time?'",grey);
            print("\nTo start using Me, please enter some basic information below when prompted.",grey);
            newline();

            newline();
            print("What is your name: ",cyan);
            readStr(name,128);

            while (!birthYearValid)
            {
                newline();
                print("What year were you born in: ",cyan);
                readStr(birthYear,5);
                birthYearInt = stoi(birthYear);

                // need to make this always the current year + 1
                if (birthYearInt < 2016 && birthYearInt > 1900)
                {
                    birthYearValid = true;
                    print(" Good",light_green);
                }

                if (!birthYearValid)
                {
                    print(" Invalid",bright_red);
                }
            }


            while (!birthDateValid)
            {
                newline();
                print("What day of the month were you born in: ",cyan);
                readStr(birthDate,3);
                birthDateInt = stoi(birthDate);

                if (birthDateInt < 32)
                {
                    birthDateValid = true;
                    print(" Good",light_green);
                }

                if (!birthDateValid)
                {
                    print(" Invalid",bright_red);
                }
            }

            while (!birthMonthValid)
            {
                newline();
                print("What month were you born in: ",cyan);
                readStr(birthMonth,128);
                birthMonth = toUpper(birthMonth);

                if (findInDictionary("me/setup/month.text",birthMonth))
                {
                    birthMonthValid = true;
                    print(" Good",light_green);
                }

                if (!birthMonthValid)
                {
                    print(" Invalid",bright_red);
                }
            }

            while (!continentValid)
            {

                newline();
                print("What continent do you live in: ",cyan);
                readStr(continent,128);
                continent = toUpper(continent);

                if (findInDictionary("me/setup/continent.text",continent))
                {
                    continentValid = true;
                    print(" Good",light_green);
                }

                if (!continentValid)
                {
                    print(" Invalid",bright_red);
                }
            }


            while (!countryValid)
            {
                newline();
                print("What country do you live in: ",cyan);
                readStr(country,128);
                country = toUpper(country);

                if (findInDictionary("me/setup/country.text",country))
                {
                    countryValid = true;
                    print(" Good",light_green);
                }

                if (!countryValid)
                {
                    print(" Invalid",bright_red);
                }
            }

            while (!stateValid)
            {
                newline();
                print("What state/province do you currently live in: ",cyan);
                readStr(state,128);
                state = toUpper(state);

                if (findInDictionary("me/setup/state.text",state))
                {
                    stateValid = true;
                    print(" Good",light_green);
                }

                if (!stateValid)
                {
                    print(" Invalid",bright_red);
                }
            }

            newline();
            print("What city do you live in: ",cyan);
            readStr(city,128);

            while (!zipValid)
            {
                newline();
                print("What is the zip/post code in your area: ",cyan);
                readStr(zip, 17);
                zipInt = htoi(zip);
                if (zipInt > 0)
                {
                    zipValid = true;
                    print(" Good",light_green);
                }
            }

            newline();
            hasSetup = "true";
            print("Me is now ready to use!",grey);

            newline();
            print("When Me dosen't know information, it can ask you for help.",grey);
        }
        else
        {
            print("\nYou have already completed the setup process for Me!",purple);
        }
    }
    else if (streql(splitArg(args, 1),""))
    {
        querying = true;
        char* meArgs = "";

        while (querying)
        {
            newline();

            //meArgs = "";
            print("me>  ",green);
            readStr(meArgs,128);

            print(answer(meArgs,0),red);
        }
    }
    else
    {
        answer(args,1);
    }
}
