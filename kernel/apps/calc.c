#include "calc.h"

#include "../inc/intTypeDefs.h"
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
int isNegative = 0;//Not negative

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

int isMathOperator(int charToCheck){
    if(charToCheck == 42 || charToCheck == 43 || charToCheck == 45 || charToCheck == 47)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void calcHelp()
{
    print("\nCalculator help: ", 0x0F);
    print("\n[HELP TEXT HERE]", 0x0F);
}

void calc(char calcArgs[CALCSIZE/2])
{
    if(calcArgs[1] == 45 && calcArgs[2] == 104){
	calcHelp();
    }else{

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
			if(calcInput[i] == 42 || calcInput[i] == 43 || calcInput[i] == 45 || calcInput[i] == 47){
				//check if user enter negative and not minus operator
				if(calcInput[i] == 45 && isMathOperator(calcInput[i+1]) == 0){
					isNegative = 1;
				}
				else
				{
					strNum = tempNum;
					//Set negative for the number before math operator
					if(isNegative == 1)
					{
						strNum *= -1;
					}
					tempNum = 0;
					isNegative = 0;
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
    if(isNegative == 1)
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

    isNegative = 0;
    }
}
