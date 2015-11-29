#include "calc.h"

// initialize the math storage variables
int mathOp[CALCSIZE];
double strNum[CALCSIZE];
int strNumCount = 0, tempNum = -1;
bool isNegative = false, isUnaryNot = false;

// concatinating for calculator
int concat(int x, int y)
{
    if(x < 0) {
        return y;
    }
    if(y < 0) {
        return x;
    }
    int pow = 10;
    while(y >= pow)
    {
        pow*= 10;
    }
    return x * pow + y;
}

static inline bool isMathOperator(char charToCheck) {
    return charToCheck == '+' || charToCheck == '-' || charToCheck == '*' || charToCheck == '/' || charToCheck == '%' || charToCheck == '&' || charToCheck == '|' || charToCheck == '^' || charToCheck == '~' || charToCheck == '<' || charToCheck == '>' || charToCheck == '=';
}

void calcHelp()
{
    print("\nCalculator help: ", 0x0F);
    print("\n[HELP TEXT HERE]", 0x0F);
}

//Prints an error based on the error ID
void mathError(uint8 ID)
{
    newline();
    switch (ID)
    {
    case 0:
        print("Cannot start with an operator", 0x04);
        break;
    case 1:
        print("Cannot divide by 0", 0x04);
        break;
    case 2:
        print("Cannot have 2 operators side by side", 0x04);
        break;
    default:
        print("Unknown math exception: ", 0x04);
        printint(ID, 0x04);
        break;
    }
}

void calc(string args)
{
    if(strEql(args," -h"))
    {
       calcHelp();
    }
    else if(strEql(args," -pi"))
    {
        print("\n3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989",0x08);
    }
    else if(strEql(args," -pow"))
    {
        newline();
        print("Number>  ",0x08);
        readStr(calcInput, CALCSIZE);
        newline();
    	char ans = powerOfTen((int)calcInput);
    	printch(ans, 0x0F);
    }
    else
    {
        print("\nUse calc -h for help\n>  ", 0x0F);

        readStr(calcInput, CALCSIZE);
        strcat(calcInput, "+0"); // Unary related hack! do not delete
        
        for(int i = 0; i < CALCSIZE; i++)
        {
            if((calcInput[i] == 0) || (calcInput[i] == 10))
                break;
            else
            {
                int pInput = ctoi(calcInput[i]);
                // -1 means invalid char, 62 is + and 6 is /
                if ((pInput != -1) && (pInput != 62) && (pInput != 63))
                    tempNum = concat(tempNum, pInput);
                else {
                    // Properly check for math operator
                    if(isMathOperator(calcInput[i]))
                    {
                        //check if user enter negative and not minus operator
                        if(tempNum < 0) //If tempNum doesn't have a value
                        {
                            if(calcInput[i] == '-')
                            {
                                if(isNegative || isUnaryNot)
                                {
                                    mathError(2);
                                    return;
                                }
                                isNegative = true;
                            }
                            else if(calcInput[i] == '~')
                            {
                                if(isNegative || isUnaryNot)
                                {
                                    mathError(2);
                                    return;
                                }
                                isUnaryNot = true;
                            }
                            else
                            {
                                mathError(strNumCount == 0 ? 0 : 2);
                                return;
                            }
                        }
                        else
                        {
                            if(isNegative)
                                tempNum *= -1;
                            else if (isUnaryNot)
                                tempNum = ~tempNum;
                            strNum[strNumCount] = tempNum;
                            mathOp[strNumCount++] = calcInput[i]; 	// set math operator
                            tempNum = -1;
                            isNegative = false;
                            isUnaryNot = false;
                        }
                    }
                }
            }
        }
        strNum[strNumCount++] = tempNum;
        // '<' '>' and '='
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == '<')
            {
                strNum[i] = strNum[i] < strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '>')
            {
                strNum[i] = strNum[i] > strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '%')
            {
                strNum[i] = strNum[i] == strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
        }
        //'*' '/' and '%'
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == '*')
            {
                strNum[i] *= strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '/')
            {
                if(strNum[i+1] == 0)
                {
                    mathError(1);
                    return;
                }
                strNum[i] /= strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '%')
            {
                if(strNum[i+1] == 0)
                {
                    mathError(1);
                    return;
                }
                strNum[i] = ((long) strNum[i]) % ((long) strNum[i+1]);
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
        }
        
        //Then do + and -
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == '+')
            {
                strNum[i] += strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '-')
            {
                strNum[i] -= strNum[i+1];
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
        }
        
        //Then do '&', '|', and '^'
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == '&')
            {
                strNum[i] = ((long) strNum[i]) & ((long) strNum[i+1]);
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '|')
            {
                strNum[i] = ((long) strNum[i]) | ((long) strNum[i+1]);
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
            else if(mathOp[i] == '^')
            {
                strNum[i] = ((long) strNum[i]) ^ ((long) strNum[i+1]);
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    strNum[j] = strNum[j+1];
                }
                strNumCount--;
                i--;
                for(int j = i+1; j < strNumCount-1; j++)
                {
                    mathOp[j] = mathOp[j+1];
                }
            }
        }
        newline();
        printint(round(strNum[0]), 0x0F);

        //Reset operational variable to its default state
        tempNum = -1;
        strNumCount = 0;
        isNegative = false;
        isUnaryNot = false;
    }
}
