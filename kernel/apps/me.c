#include "me.h"

#define curWord toUpper(splitArg(args, tmp))

// has the user finished the 'me' setup process?
bool hasSetup = false;

// the users ZIP/Post Code
string zip;

// variables to determine if the entered values are valid based on the Me database
bool birthYearValid = false;
bool birthDateValid = false;
bool birthMonthValid = false;

bool continentValid = false;
bool countryValid = false;
bool stateValid = false;
bool cityValid = false;
bool zipValid = false;

// Are you currently in the 'me' Command Line interface?
bool querying = false;

// this is shown at the top of every unanswered question during 'me' setup
void meHeader()
{
    clearLine(0,26,0x88);

    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Me Setup Process", 0x3D, 21, 9);
}

// we show this is a correct answer is given during the 'me' setup
void goodAnswer()
{
    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Good", 0x32, 21, 9);
}

// this is shown when someone enters an invalid answer during the 'me' setup
void badAnswer()
{
    drawFrame(header_background, 20, 8, 60, 11);
    printAt("Invalid", 0x34, 21, 9);
}

void me(string args)
{
    if (!hasSetup)
    {
        if (streql(splitArg(args, 1), "-h"))
        {
            // a super legit help section brought to you by @plankp
            print("\nMe is here to help you... Believe me...", brown);
        }
        else if (streql(splitArg(args, 1), "test") && !hasSetup)
        {
            hasSetup = true;
            messageBox("\nYou have skipped the Me setup process.");
        }
        else if (!hasSetup)
        {
            meHeader();

            messageBox("\nWelcome to Me. To start using Me,\n\rpress <RET> to setup Me.");

            meHeader();

            name = messageBox_I("What is your name?");

            meHeader();

            while (!birthYearValid)
            {
                birthYear = messageBox_I("What year were you born in?");
                birthYearInt = stoi(birthYear);

                // need to make this always the current year + 1
                if (birthYearInt < getTime("year") && birthYearInt > 1900)
                {
                    birthYearValid = true;
                    goodAnswer();
                }

                if (!birthYearValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            while (!birthDateValid)
            {
                newline();
                birthDate = messageBox_I("What day were you born on");
                birthDateInt = stoi(birthDate);

                if (birthDateInt < 32)
                {
                    birthDateValid = true;
                    goodAnswer();
                }

                if (!birthDateValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            while (!birthMonthValid)
            {
                newline();
                birthMonth = messageBox_I("What month were you born in?");
                birthMonth = toUpper(birthMonth);

                if (findInDictionary("me/setup/month.text",birthMonth))
                {
                    birthMonthValid = true;
                    goodAnswer();
                }

                if (!birthMonthValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            while (!continentValid)
            {

                newline();
                continent = messageBox_I("What continent do you live in?");
                continent = toUpper(continent);

                if (findInDictionary("me/setup/continent.text",continent))
                {
                    continentValid = true;
                    goodAnswer();
                }

                if (!continentValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            while (!countryValid)
            {
                newline();
                country = messageBox_I("What country do you live in?");
                country = toUpper(country);

                if (findInDictionary("me/setup/country.text",country))
                {
                    countryValid = true;
                    goodAnswer();
                }

                if (!countryValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            while (!stateValid)
            {
                newline();
                state = messageBox_I("What state/province do you live in?");
                state = toUpper(state);

                if (findInDictionary("me/setup/state.text",state))
                {
                    stateValid = true;
                    goodAnswer();
                }

                if (!stateValid)
                {
                    badAnswer();
                }
            }

            meHeader();

            newline();
            city = messageBox_I("What city/town do you live in?");

            clearLine(0,26,0x88);

            drawFrame(header_background, 20, 8, 60, 11);
            printAt("Me Setup Process", 0x3D, 21, 9);

            while (!zipValid)
            {
                newline();
                zip = messageBox_I("What is your zip/post code?");
                zipInt = htoi(zip);
                if (zipInt > 0)
                {
                    zipValid = true;
                    goodAnswer();
                }
                else
                {
                    badAnswer();
                }
            }

            meHeader();

            hasSetup = "true";
            messageBox("Me is now ready to use! Type 'me' on\n\rthe command line to begin.");

            printIntro();
            drawBorder(screen_background, 0, 4, 80, sh - 1);

            actualY = 5;
            printAt("Q-Kernel>  ", light_grey, 1, actualY);
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
