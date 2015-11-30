#include "me.h"

// Here we declare all the arrays we need for Me runtime
// We should probably move this to another file soon
char *months[] = {
    "january",
    "febuary",
    "march",
    "april",
    "may",
    "june",
    "july",
    "august",
    "september",
    "october",
    "november",
    "december"
};

char *continents[] = {
    "australia",
    "africa",
    "antarctica",
    "europe",
    "north america",
    "south america",
    "asia"
};

// Thanks to https://www.countries-ofthe-world.com/all-countries.html
// For a list of countries that I have turned into an array here
char *countries[] = {
  "afghanistan",
  "albania",
  "algeria",
  "andorra",
  "angola",
  "antigua and barbuda",
  "argentina",
  "armenia",
  "australia",
  "austria",
  "azerbaijan",
  "bahamas",
  "bahrain",
  "bangladesh",
  "barbados",
  "belarus",
  "belgium",
  "belize",
  "benin",
  "bhutan",
  "bolivia",
  "bosnia and herzegovina",
  "botswana",
  "brazil",
  "brunei",
  "bulgaria",
  "burkina faso",
  "burundi",
  "cabo verde",
  "cambodia",
  "cameroon",
  "canada",
  "central african republic",
  "chad",
  "chile",
  "china",
  "colombia",
  "comoros",
  "congo, republic of the",
  "congo, democratic republic of the",
  "costa rica",
  "cote d'ivoire",
  "croatia",
  "cuba",
  "cyprus",
  "czech republic",
  "denmark",
  "djibouti",
  "dominica",
  "dominican republic",
  "ecuador",
  "egypt",
  "el salvador",
  "equatorial guinea",
  "eritrea",
  "estonia",
  "ethiopia",
  "fiji",
  "finland",
  "france",
  "gabon",
  "gambia",
  "georgia",
  "germany",
  "ghana",
  "greece",
  "grenada",
  "guatemala",
  "guinea",
  "guinea-bissau",
  "guyana"
  "haiti",
  "iran",
  "ireland",
  "italy",
  "jamaica",
  "japan",
  "jordan",
  "kazakhstan",
  "kenya",
  "kiribati",
  "kosovo",
  "kuwait",
  "honduras",
  "hungary",
  "iceland",
  "india",
  "indonesia",
  "iraq",
  "israel",
  "kyrgyzstan",
  "laos",
  "latvia",
  "lebanon",
  "lesotho",
  "liberia",
  "libya",
  "liechtenstein",
  "lithuania",
  "luxembourg",
  "macedonia",
  "madagascar",
  "malawi",
  "malaysia",
  "maldives",
  "mali",
  "malta",
  "marshall Islands",
  "mauritania",
  "mauritius",
  "mexico",
  "micronesia",
  "moldova",
  "monaco",
  "mongolia",
  "montenegro",
  "morocco",
  "mozambique",
  "myanmar (burma)",
  "namibia",
  "nauru",
  "nepal",
  "netherlands",
  "new zealand",
  "nicaragua",
  "niger",
  "nigeria",
  "north korea",
  "norway",
  "oman",
  "pakistan",
  "palau",
  "palestine",
  "panama",
  "papua new guinea",
  "paraguay",
  "peru",
  "philippines",
  "poland",
  "portugal",
  "qatar",
  "romania",
  "russia",
  "rwanda",
  "st. kitts and nevis",
  "st. lucia",
  "st. vincent and the grenadines",
  "samoa",
  "san marino",
  "sao tome and principe",
  "saudi arabia",
  "senegal",
  "serbia",
  "seychelles",
  "sierra leone",
  "slovakia",
  "singapore",
  "slovenia",
  "solomon islands",
  "somalia",
  "south africa",
  "south korea",
  "south sudan",
  "spain",
  "sri lanka",
  "suriname",
  "sudan",
  "swaziland",
  "sweden",
  "switzerland",
  "syria",
  "taiwan",
  "tajikistan",
  "tanzania",
  "thailand",
  "timor-leste",
  "togo",
  "tonga",
  "trinidad and tobago",
  "tunisia",
  "turkey",
  "turkmenistan",
  "tuvalu",
  "uganda",
  "ukraine",
  "uae",
  "united arab emirates",
  "united kingdom",
  "uk",
  "united states of america",
  "usa",
  "uruguay",
  "uzbekistan",
  "vanuatu",
  "holy see",
  "vatican city",
  "venezuela",
  "vietnam",
  "yemen",
  "zambia",
  "zimbabwe"
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
            print("What is your name: ",0x0B);
            readStr(name,128);

            newline();
            print("What year were you born in: ",0x0B);
            readStr(birthYear,5); // Only four digits is possible

            newline();
            print("What day of the month were you born in: ",0x0B);
            readStr(birthDate,3); // Only max 2 digits is possible

            while (!birthMonthValid)
            {
                newline();
                print("What month were you born in: ",0x0B);
                readStr(birthMonth,128);

                for(int tmp = 0; tmp < 12; tmp++)
                {
                    if (strEql(months[tmp], toLower(birthMonth)))
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

                for(int tmp = 0; tmp < 7; tmp++)
                {
                    if (strEql(continents[tmp], toLower(continent)))
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

                for(int tmp = 0; tmp < 246; tmp++)
                {
                    if (strEql(countries[tmp], toLower(country)))
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
