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
    "December",
};

char *continents[] = {
    "Australia",
    "Africa",
    "Antarctica",
    "Europe",
    "North America",
    "South America",
    "Asia",
};

// Thanks to https://www.countries-ofthe-world.com/all-countries.html
// For a list of countries that I have turned into an array here
char *months[] = {
    "JANUARY",
    "FEBUARY",
    "MARCH",
    "APRIL",
    "MAY",
    "JUNE",
    "JULY",
    "AUGUST",
    "SEPTEMBER",
    "OCTOBER",
    "NOVEMBER",
    "DECEMBER",
};

char *continents[] = {
    "AUSTRALIA",
    "AFRICA",
    "ANTARCTICA",
    "EUROPE",
    "NORTH AMERICA",
    "SOUTH AMERICA",
    "ASIA",
};

// THANKS TO HTTPS://WWW.COUNTRIES-OFTHE-WORLD.COM/ALL-COUNTRIES.HTML
// FOR A LIST OF COUNTRIES THAT I HAVE TURNED INTO AN ARRAY HERE
char *countries[] = {
    "AFGHANISTAN",
    "ALBANIA",
    "ALGERIA",
    "ANDORRA",
    "ANGOLA",
    "ANTIGUA AND BARBUDA",
    "ARGENTINA",
    "ARMENIA",
    "AUSTRALIA",
    "AUSTRIA",
    "AZERBAIJAN",
    "BAHAMAS",
    "BAHRAIN",
    "BANGLADESH",
    "BARBADOS",
    "BELARUS",
    "BELGIUM",
    "BELIZE",
    "BENIN",
    "BHUTAN",
    "BOLIVIA",
    "BOSNIA AND HERZEGOVINA",
    "BOTSWANA",
    "BRAZIL",
    "BRUNEI",
    "BULGARIA",
    "BURKINA FASO",
    "BURUNDI",
    "CABO VERDE",
    "CAMBODIA",
    "CAMEROON",
    "CANADA",
    "CENTRAL AFRICAN REPUBLIC",
    "CHAD",
    "CHILE",
    "CHINA",
    "COLOMBIA",
    "COMOROS",
    "CONGO, REPUBLIC OF THE",
    "CONGO, DEMOCRATIC REPUBLIC OF THE",
    "COSTA RICA",
    "COTE D'IVOIRE",
    "CROATIA",
    "CUBA",
    "CYPRUS",
    "CZECH REPUBLIC",
    "DENMARK",
    "DJIBOUTI",
    "DOMINICA",
    "DOMINICAN REPUBLIC",
    "ECUADOR",
    "EGYPT",
    "EL SALVADOR",
    "EQUATORIAL GUINEA",
    "ERITREA",
    "ESTONIA",
    "ETHIOPIA",
    "FIJI",
    "FINLAND",
    "FRANCE",
    "GABON",
    "GAMBIA",
    "GEORGIA",
    "GERMANY",
    "GHANA",
    "GREECE",
    "GRENADA",
    "GUATEMALA",
    "GUINEA",
    "GUINEA-BISSAU",
    "GUYANA"
    "HAITI",
    "HONDURAS",
    "HUNGARY",
    "ICELAND",
    "INDIA",
    "INDONESIA",
    "IRAN",
    "IRAQ",
    "IRELAND",
    "ISRAEL",
    "ITALY",
    "JAMAICA",
    "JAPAN",
    "JORDAN",
    "KAZAKHSTAN",
    "KENYA",
    "KIRIBATI",
    "KOSOVO",
    "KUWAIT",
    "KYRGYZSTAN",
    "LAOS",
    "LATVIA",
    "LEBANON",
    "LESOTHO",
    "LIBERIA",
    "LIBYA",
    "LIECHTENSTEIN",
    "LITHUANIA",
    "LUXEMBOURG",
    "MACEDONIA",
    "MADAGASCAR",
    "MALAWI",
    "MALAYSIA",
    "MALDIVES",
    "MALI",
    "MALTA",
    "MARSHALL ISLANDS",
    "MAURITANIA",
    "MAURITIUS",
    "MEXICO",
    "MICRONESIA",
    "MOLDOVA",
    "MONACO",
    "MONGOLIA",
    "MONTENEGRO",
    "MOROCCO",
    "MOZAMBIQUE",
    "MYANMAR (BURMA)",
    "NAMIBIA",
    "NAURU",
    "NEPAL",    "HONDURAS",
    "HUNGARY",
    "ICELAND",
    "INDIA",
    "INDONESIA",
    "IRAN",
    "IRAQ",
    "IRELAND",
    "ISRAEL",
    "ITALY",
    "JAMAICA",
    "JAPAN",
    "JORDAN",
    "KAZAKHSTAN",
    "KENYA",
    "KIRIBATI",
    "KOSOVO",
    "KUWAIT",
    "KYRGYZSTAN",
    "LAOS",
    "LATVIA",
    "LEBANON",
    "LESOTHO",
    "LIBERIA",
    "LIBYA",
    "LIECHTENSTEIN",
    "LITHUANIA",
    "LUXEMBOURG",
    "MACEDONIA",
    "MADAGASCAR",
    "MALAWI",
    "MALAYSIA",
    "MALDIVES",
    "MALI",
    "MALTA",
    "MARSHALL ISLANDS",
    "MAURITANIA",
    "MAURITIUS",
    "MEXICO",
    "MICRONESIA",
    "MOLDOVA",
    "MONACO",
    "MONGOLIA",
    "MONTENEGRO",
    "MOROCCO",
    "MOZAMBIQUE",
    "MYANMAR (BURMA)",
    "NAMIBIA",
    "NAURU",
    "NEPAL",
    "NETHERLANDS",
    "NEW ZEALAND",
    "NICARAGUA",
    "NIGER",
    "NIGERIA",
    "NORTH KOREA",
    "NORWAY",
    "OMAN",
    "PAKISTAN",
    "PALAU",
    "PALESTINE",
    "PANAMA",
    "PAPUA NEW GUINEA",
    "PARAGUAY",
    "PERU",
    "PHILIPPINES",
    "POLAND",
    "PORTUGAL",
    "QATAR",
    "ROMANIA",
    "RUSSIA",
    "RWANDA",
    "ST. KITTS AND NEVIS",
    "ST. LUCIA",
    "ST. VINCENT AND THE GRENADINES",
    "SAMOA",
    "SAN MARINO",
    "SAO TOME AND PRINCIPE",
    "SAUDI ARABIA",
    "SENEGAL",
    "SERBIA",
    "SEYCHELLES",
    "SIERRA LEONE",
    "SLOVAKIA",
    "SINGAPORE",
    "SLOVENIA",
    "SOLOMON ISLANDS",
    "SOMALIA",
    "SOUTH AFRICA",
    "SOUTH KOREA",
    "SOUTH SUDAN",
    "SPAIN",
    "SRI LANKA",
    "SURINAME",
    "SUDAN",
    "SWAZILAND",
    "SWEDEN",
    "SWITZERLAND",
    "SYRIA",
    "TAIWAN",
    "TAJIKISTAN",
    "TANZANIA",
    "THAILAND",
    "TIMOR-LESTE",
    "TOGO",
    "TONGA",
    "TRINIDAD AND TOBAGO",
    "TUNISIA",
    "TURKEY",
    "TURKMENISTAN",
    "TUVALU",
    "UGANDA",
    "UKRAINE",
    "UNITED ARAB EMIRATES",
    "UK (UNITED KINGDOM)",
    "USA (UNITED STATES OF AMERICA)",
    "URUGUAY",
    "UZBEKISTAN",
    "VANUATU",
    "VATICAN CITY (HOLY SEE)",
    "VENEZUELA",
    "VIETNAM",
    "YEMEN",
    "ZAMBIA",
    "ZIMBABWE"
    "NETHERLANDS",
    "NEW ZEALAND",
    "NICARAGUA",
    "NIGER",
    "NIGERIA",
    "NORTH KOREA",
    "NORWAY",
    "OMAN",
    "PAKISTAN",
    "PALAU",
    "PALESTINE",
    "PANAMA",
    "PAPUA NEW GUINEA",
    "PARAGUAY",
    "PERU",
    "PHILIPPINES",
    "POLAND",
    "PORTUGAL",
    "QATAR",
    "ROMANIA",
    "RUSSIA",
    "RWANDA",
    "ST. KITTS AND NEVIS",
    "ST. LUCIA",
    "ST. VINCENT AND THE GRENADINES",
    "SAMOA",
    "SAN MARINO",
    "SAO TOME AND PRINCIPE",
    "SAUDI ARABIA",
    "SENEGAL",
    "SERBIA",
    "SEYCHELLES",
    "SIERRA LEONE",
    "SLOVAKIA",
    "SINGAPORE",
    "SLOVENIA",
    "SOLOMON ISLANDS",
    "SOMALIA",
    "SOUTH AFRICA",
    "SOUTH KOREA",
    "SOUTH SUDAN",
    "SPAIN",
    "SRI LANKA",
    "SURINAME",
    "SUDAN",
    "SWAZILAND",
    "SWEDEN",
    "SWITZERLAND",
    "SYRIA",
    "TAIWAN",
    "TAJIKISTAN",
    "TANZANIA",
    "THAILAND",
    "TIMOR-LESTE",
    "TOGO",
    "TONGA",
    "TRINIDAD AND TOBAGO",
    "TUNISIA",
    "TURKEY",
    "TURKMENISTAN",
    "TUVALU",
    "UGANDA",
    "UKRAINE",
    "UNITED ARAB EMIRATES",
    "UK (UNITED KINGDOM)",
    "USA (UNITED STATES OF AMERICA)",
    "URUGUAY",
    "UZBEKISTAN",
    "VANUATU",
    "VATICAN CITY (HOLY SEE)",
    "VENEZUELA",
    "VIETNAM",
    "YEMEN",
    "ZAMBIA",
    "ZIMBABWE",
};

// Here we setup all the boolean values that we need for Me
// We should probably move this to another file soon when it gets longer
bool hasSetup = false;

bool birthYearValid = false;
bool birthDateValid = false;
bool birthMonthValid = false;

bool continentValid = false;
bool countryValid = false;
bool stateValid = false;
bool cityValid = false;
bool zipValid = false;

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

            newline();
            print("What day of the month were you born in: ",0x0B);
            readStr(birthDate,3);

            while (!birthMonthValid)
            {
                newline();
                print("What month were you born in: ",0x0B);
                readStr(birthMonth,128);

                for(int tmp = 0; tmp < 12; tmp++)
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

                for(int tmp = 0; tmp < 7; tmp++)
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

                for(int tmp = 0; tmp < 249; tmp++)
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
