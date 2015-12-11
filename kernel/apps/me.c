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
            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            messageBox("\nWelcome to Me. To start using Me,\n\rpress <RET> to setup Me.");
            newline();

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            newline();
            name = messageBox_I("What is your name?");

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

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
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!birthDateValid)
            {
                newline();
                birthDate = messageBox_I("What day were you born on");
                birthDateInt = stoi(birthDate);

                if (birthDateInt < 32)
                {
                    birthDateValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }

                if (!birthDateValid)
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!birthMonthValid)
            {
                newline();
                birthMonth = messageBox_I("What month were you born in?");
                birthMonth = toUpper(birthMonth);

                if (findInDictionary("me/setup/month.text",birthMonth))
                {
                    birthMonthValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }

                if (!birthMonthValid)
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!continentValid)
            {

                newline();
                continent = messageBox_I("What continent do you live in?");
                continent = toUpper(continent);

                if (findInDictionary("me/setup/continent.text",continent))
                {
                    continentValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }

                if (!continentValid)
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!countryValid)
            {
                newline();
                country = messageBox_I("What country do you live in?");
                country = toUpper(country);

                if (findInDictionary("me/setup/country.text",country))
                {
                    countryValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }

                if (!countryValid)
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!stateValid)
            {
                newline();
                state = messageBox_I("What state/province do you live in?");
                state = toUpper(state);

                if (findInDictionary("me/setup/state.text",state))
                {
                    stateValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }

                if (!stateValid)
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            newline();
            city = messageBox_I("What city/town do you live in?");

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            while (!zipValid)
            {
                newline();
                zip = messageBox_I("What is your zip/post code?");
                zipInt = htoi(zip);
                if (zipInt > 0)
                {
                    zipValid = true;
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Good", 0x32, 21, 9);
                }
                else
                {
                    drawFrame(header_background, 20, 8, 60, 11);
                    printAt("Invalid", 0x34, 21, 9);
                }
            }

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", green, 21, 9);

            hasSetup = "true";
            messageBox("Me is now ready to use! Type 'me' on the command line to begin.");

            printIntro();

            drawBorder(screen_background, 0, 4, 80, sh - 1);
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
