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

char *continents[] = {
    "Australia",
    "Africa",
    "Antarctica",
    "Europe",
    "North America",
    "South America",
    "Asia"
};

// Thanks to https://www.countries-ofthe-world.com/all-countries.html
// For a list of countries that I have turned into an array here
char *countries[] = {
    "Afghanistan",
    "Albania",
    "Algeria",
    "Andorra",
    "Angola",
    "Antigua and Barbuda",
    "Argentina",
    "Armenia",
    "Australia",
    "Austria",
    "Azerbaijan",
    "Bahamas",
    "Bahrain",
    "Bangladesh",
    "Barbados",
    "Belarus",
    "Belgium",
    "Belize",
    "Benin",
    "Bhutan",
    "Bolivia",
    "Bosnia and Herzegovina",
    "Botswana",
    "Brazil",
    "Brunei",
    "Bulgaria",
    "Burkina Faso",
    "Burundi",
    "Cabo Verde",
    "Cambodia",
    "Cameroon",
    "Canada",
    "Central African Republic",
    "Chad",
    "Chile",
    "China",
    "Colombia",
    "Comoros",
    "Congo, Republic of the",
    "Congo, Democratic Republic of the",
    "Costa Rica",
    "Cote d'Ivoire",
    "Croatia",
    "Cuba",
    "Cyprus",
    "Czech Republic",
    "Denmark",
    "Djibouti",
    "Dominica",
    "Dominican Republic",
    "Ecuador",
    "Egypt",
    "El Salvador",
    "Equatorial Guinea",
    "Eritrea",
    "Estonia",
    "Ethiopia",
    "Fiji",
    "Finland",
    "France",
    "Gabon",
    "Gambia",
    "Georgia",
    "Germany",
    "Ghana",
    "Greece",
    "Grenada",
    "Guatemala",
    "Guinea",
    "Guinea-Bissau",
    "Guyana"
};

// Here we setup all the boolean values that we need for Me
// We should probably move this to another file soon when it gets longer
bool hasSetup = false;

bool birthYearValid;
bool birthDateValid;
bool birthMonthValid = false;

bool continentValid = false;
bool countryValid = false;
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

                for(int tmp = 0; tmp < 6; tmp++)
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

            while (!continentValid)
            {
                newline();
                print("What continent do you live in: ",0x02);
                readStr(continent,128);

                for(int tmp = 0; tmp < 6; tmp++)
                {
                    if (strEql(continents[tmp],continent))
                    {
                        continentValid = true;
                    }
                }

                if (!continentValid)
                {
                    print("\nThe continent you entered appears to be invalid. Please enter the correct continent you live in.",0x0C);
                }
            }


            while (!countryValid)
            {
                newline();
                print("What country do you live in: ",0x02);
                readStr(country,128);

                for(int tmp = 0; tmp < 71; tmp++)
                {
                    if (strEql(countries[tmp],country))
                    {
                        countryValid = true;
                    }
                }

                if (!countryValid)
                {
                    print("\nThe country you entered appears to be invalid. Please enter the correct country you live in.",0x0C);
                }
            }

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
