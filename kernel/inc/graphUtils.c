#include "graphUtils.h"

// we set any yet-to-be defined values that are of type 'int' to -96678
// we do this to use that number as a placeholder for a real value
// the reason I am using -96678 as our placeholder is because -96678
// is an unlikely number to be used in a calculation or math formula
#define UNDEFINED_INT -96678
#define FUNCTIONSTR "((x^2) + x-6)"

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
                printint(ctoi(math[tmp]),magenta);
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

        printch(math[tmp],green);

        tmp++;
    }


    if (bracketLevel < 0)
    {
        print("\nToo Many Closing Brackets ')' in Algorithm",red);
        return 0;
    }
    else if (bracketLevel > 0)
    {
        print("\nToo Many Opening Brackets '(' in Algorithm",red);
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

// evalutae the Y value at any point during a function execution based on X value
int stepFunc(int xVal)
{
    return (int)((xVal^2) + xVal-6);
}

void evalFunc(string mathFunction)
{
    printint(evalString(mathFunction),green);

    newline();

    int x = stoi(mathFunction);
    int y;

    print("\nFunction: ",bright_red);
    print(FUNCTIONSTR,green);

    while (x < (stoi(mathFunction) * (-1) + 1))
    {
        y = stepFunc(x);
        print("\nCurrent X: ",red);
        printint(x,grey);
        print(" Current Y: ",red);
        printint(y,grey);
        x++;
    }
}

// this is going to be a calculus function to return the gradient rise at any point on a graph with a run as set below
int getRise(int x)
{
    // we currently have no use for this
    //double run = 0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001;

    // we are currently limited to a single function in calculus so this will actually be the correct answer
    return x * 2;
}
