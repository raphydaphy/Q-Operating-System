#include "skip.h"

#define FUNCTIONSTR "((x^2) + x-6)"

// char* function = "((xVal^2)+xVal-6)";

char* mathFunction = "(1+1)";

// we set any yet-to-be defined values that are of type 'int' to -96678
// we do this to use that number as a placeholder for a real value
// the reason I am using -96678 as our placeholder is because -96678
// is an unlikely number to be used in a calculation or math formula
#define UNDEFINED_INT -96678

int evalString(string math)
{
    // this will determine when our while statement should stop running
    bool over = false;

    // a counter variable for our while statement below
    uint8 tmp = 0;

    // how deeply indented the brackets '(' or ')' are at any given time
    int8 bracketLevel = 0;

    // what the current math operation we are performing is (+, -, /, ^, etc)
    char curOpp = 'Z';

    // the most recently entered number
    // lastNum[0] = the last entered number as an integer data type
    // lastNum[1] =
    // lastNum[2] = the bracketing level of the last entered number
    int lastNum[3];
    lastNum[0] = UNDEFINED_INT;

    // the most recently calculated result
    int lastResult = UNDEFINED_INT;

    // the answer to the entire formula
    int answer = UNDEFINED_INT;

    while(!over)
    {
        if (math[tmp] == ' ')
        {
            over = true;
        }
        else if (math[tmp] == '(')
        {
            bracketLevel++;
        }
        else if (math[tmp] == ')')
        {
            bracketLevel--;
        }
        else if (math[tmp] == '+')
        {
            curOpp = '+';
        }
        else if (ctoi(math[tmp]) < 10 && ctoi(math[tmp]) > -1)
        {
            if (curOpp == 'Z')
            {
                // the number has been entered before any operation signs
                printint(ctoi(math[tmp]),0x0D);
            }
            else if (bracketLevel == 0)
            {
                if (curOpp == '+')
                {
                    // add the current number with the most recently entered number
                    if (answer != UNDEFINED_INT)
                    {
                        answer += ctoi(math[tmp]) + lastNum[0];
                    }
                    else
                    {
                        answer = ctoi(math[tmp]) + lastNum[0];
                    }
                }
            }
            else if (bracketLevel > 0)
            {
                if (curOpp == '+')
                {
                    // add the current number with the most recently entered number
                    // however this will only run if the latest entered number is
                    // at the same or higher bracketing level and bracketLevel > 0
                    if (lastNum[2] >= bracketLevel)
                    {
                        if (answer != UNDEFINED_INT)
                        {
                            answer += ctoi(math[tmp]) + lastNum[0];
                        }
                        else
                        {
                            answer += ctoi(math[tmp]) + lastNum[0];
                        }
                    }
                }
            }



            lastNum[0] = ctoi(math[tmp]);
            lastNum[2] = bracketLevel;
        }

        printch(math[tmp],0x0A);

        tmp++;
    }


    if (bracketLevel < 0)
    {
        print("\nToo Many Closing Brackets ')' in Algorithm",0x04);
        return 0;
    }
    else if (bracketLevel > 0)
    {
        print("\nToo Many Opening Brackets '(' in Algorithm",0x04);
        return 0;
    }

    if (answer != UNDEFINED_INT)
    {
        return answer;
    }
    else
    {
        return lastResult;
    }
}

int graphFunction(int xVal)
{
    return (int)((xVal^2) + xVal-6);
}

void skip(string args) {
    newline();

    printint(evalString(mathFunction),0x0A);

    newline();

    int x = stoi(splitArg(args,1));
    int y;

    print("\nFunction: ",0x0C);
    print(FUNCTIONSTR,0x0A);

    while (x < (stoi(splitArg(args,1)) * (-1) + 1))
    {
        y = graphFunction(x);
        print("\nCurrent X: ",0x04);
        printint(x,0x03);
        print(" Current Y: ",0x04);
        printint(y,0x03);
        x++;
    }
}
