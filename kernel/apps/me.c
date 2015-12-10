#include "me.h"

#define curWord toUpper(splitArg(args, tmp))

bool hasSetup = false;
string zip;

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
            name = messageBox_I("What is your name?");

            while (!birthYearValid)
            {
                newline();
                birthYear = messageBox_I("What year were you born in?");
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
                birthDate = messageBox_I("What day were you born on");
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
                birthMonth = messageBox_I("What month were you born in?");
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
                continent = messageBox_I("What continent do you live in?");
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
                country = messageBox_I("What country do you live in?");
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
                state = messageBox_I("What state/province do you live in?");
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
            city = messageBox_I("What city/town do you live in?");

            while (!zipValid)
            {
                newline();
                zip = messageBox_I("What is your zip/post code?");
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
            readStr(meArgs,128,false);

            print(answer(meArgs,0),red);
        }
    }
    else
    {
        answer(args,1);
    }
}
