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

void calcHelp()
{
	print("\nCalculator help: ", 0x0F);
	print("\n[HELP TEXT HERE]", 0x0F);
}
void calc() 
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
					strNum = tempNum;
					tempNum = 0;
					mathOp = calcInput[i]; 	// Treat everything else as a math operator 
								// should do for now
					break;
			}
		}
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
		printint(strNum, 0x0F);
		break;
	}

	mathError = 0;

	tempNum = 0;

	strNum = 0;

}
