#include "me.h"

#define curWord toUpper(splitArg(args, tmp))

bool hasSetup = false;

void me(string args) {
    if (strEql(splitArg(args, 1), "setup") || !hasSetup)
    {
        if (strEql(splitArg(args, 2), "skip") && !hasSetup)
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

                for(uint32 tmp = 0; tmp < arrLength(months); tmp++)
                {
                    if (strEql(months[tmp],birthMonth))
                    {
                        birthMonthValid = true;
                        print(" Good",0x02);
                    }
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

                for(uint32 tmp = 0; tmp < arrLength(continents); tmp++)
                {
                    if (strEql(continents[tmp],continent))
                    {
                        continentValid = true;
                        print(" Good",0x02);
                    }
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

                for(uint32 tmp = 0; tmp < arrLength(countries); tmp++)
                {
                    if (strEql(countries[tmp],country))
                    {
                        countryValid = true;
                        print(" Good",0x02);
                    }
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

                for(uint8 tmp = 0; tmp < arrLength(states); tmp++)
                {
                    if(strEql(states[tmp],country))
                    {
                        stateValid = true;
                        print(" Good",0x02);
                    }
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
                readStr(zip,17);

                if (strEql(country,"CANADA"))
                {
                    print(" Good Enough",0x02);
                    zipValid = true;
                }
                else
                {
                    zipInt = stoi(zip);
                    if (zipInt < 9999999999999999 && zipInt > 0)
                    {
                        zipValid = true;
                        print(" Good",0x02);
                    }

                    if (!zipValid)
                    {
                        print(" Invalid",0x0C);
                    }
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
        while (!over)
        {
            tmp++;

            if (strEql(splitArg(args, tmp),""))
            {
                over = true;
            }
            else
            {
                newline();
                printint(tmp,0x0A);
                print(" : ",0x0B);
                print(curWord,0x0A);
                print(" : ",0x0B);
                printfloat(sort(splitArg(args, tmp)),0x09);

            }
        }
    }
}
