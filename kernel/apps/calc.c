#include "calc.h"
#include "../inc/math.h"

#include "../inc/intTypeDefs.h"
#include "../inc/stringUtils.h"
#include "../inc/screenUtils.h"
#include "../inc/kbDetect.h"

#ifndef CALCSIZE
#define CALCSIZE 128
#endif


// initialize the math storage variables
int mathOp = 0;
int tempNum = 0;
int strNum = 0;
int mathError = 0; //0 no error
bool isNegative = false;

// concatinating for calculator
int concat(int x, int y)
{
    int pow = 10;
    while(y >= pow)
    {
        pow*= 10;
    }
    return x * pow + y;
}

bool isMathOperator(int charToCheck){
    return charToCheck == 42 || charToCheck == 43 || charToCheck == 45 || charToCheck == 47;
}

void calcHelp()
{
    print("\nCalculator help: ", 0x0F);
    print("\n[HELP TEXT HERE]", 0x0F);
}

void calc(string args)
{
    if(strEql(args," -h"))
    {
       calcHelp();
    }
    else if(strEql(args," -pi"))
    {
        print("\n",0x00);
        print("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989",0x08);
    }
    else if(strEql(args," -pow"))
    {
        newline();
        print("Number>  ",0x08);
        readStr(calcInput,CALCSIZE);
    	print("\n",0x00);
    	char ans = powerOfTen(calcInput);
    	print(ans,0x0F);
    }
    else
    {

    print("\nUse calc -h for help", 0x0F);
    print("\n>  ", 0x0F);

    readStr(calcInput, CALCSIZE);

    for(int i = 0; i < CALCSIZE; i++)
    {
        if(calcInput[i] == 0 || calcInput[i] == 10)
        {
            break;
        }
        else
        {
            switch (calcInput[i])
            {
                case 48:	//Number 0
                    tempNum = concat(tempNum, 0);
                    break;
                case 49:	//Number 1
                    tempNum = concat(tempNum, 1);
                    break;
                case 50:	//Number 2
                    tempNum = concat(tempNum, 2);
                    break;
                case 51:	//Number 3
                    tempNum = concat(tempNum, 3);
                    break;
                case 52:	//Number 4
                    tempNum = concat(tempNum, 4);
                    break;
                case 53:	//Number 5
                    tempNum = concat(tempNum, 5);
                    break;
                case 54:	//Number 6
                    tempNum = concat(tempNum, 6);
                    break;
                case 55:	//Number 7
                    tempNum = concat(tempNum, 7);
                    break;
                case 56:	//Number 8
                    tempNum = concat(tempNum, 8);
                    break;
                case 57:	//Number 9
                    tempNum = concat(tempNum, 9);
                    break;
                default:
			// Properly check for math operator
			if(isMathOperator(calcInput[i])){
				//check if user enter negative and not minus operator
				if(calcInput[i] == 45 && isMathOperator(calcInput[i+1])){
					isNegative = true;
				}
				else
				{
					strNum = tempNum;
					//Set negative for the number before math operator
					if(isNegative)
					{
						strNum *= -1;
					}
					tempNum = 0;
					isNegative = false;
					mathOp = calcInput[i]; 	// set math operator
				}
			}
			else
			{
				continue;
			}
                break;
            }
        }
    }
    //Set negative number for the number after math operator
    if(isNegative)
    {
        tempNum *= -1;
    }
    switch (mathOp)
    {
        case 42:
            strNum *= tempNum;
            break;
        case 43:
            strNum += tempNum;
            break;
        case 45:
            strNum -= tempNum;
            break;
        case 47:
            if(tempNum != 0)
            {
                strNum /= tempNum;
            }
        else
            mathError = 1;
            break;
        default:
            strNum -= tempNum;
            break;
    }

    newline();

    switch (mathError)
    {
        case 1:
            print("Cannot divide by 0", 0x04);
            break;
        default:
            //check for negative number first
            if(strNum < 0){
                //set number to positive
                strNum *= -1;
                //print negative sign then print the number
                print("-",0x0F);
            }
            printint(strNum, 0x0F);
            break;
    }

    //Reset operational variable to its default state

    mathError = 0;

    tempNum = 0;

    strNum = 0;

    isNegative = false;
    }
}
