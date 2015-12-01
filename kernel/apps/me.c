#include "me.h"

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
            print("What is your name: ",0x0B);
            readStr(name,128);

            newline();
            print("What year were you born in: ",0x0B);
            readStr(birthYear,5);

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

                for(int tmp = 0; tmp < arrLength(months); tmp++)
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

                for(int tmp = 0; tmp < arrLength(continents); tmp++)
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

                for(int tmp = 0; tmp < arrLength(countries); tmp++)
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

            newline();
            print("What state do you currently live in: ",0x0B);
            readStr(state,128);

            newline();
            print("What city do you live in: ",0x0B);
            readStr(city,128);

            newline();
            print("What is the zip code in your area: ",0x0B);
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
