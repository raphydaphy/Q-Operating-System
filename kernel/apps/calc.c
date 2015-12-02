#include "calc.h"

// initialize the math storage variables
int mathOp[CALCSIZE];
float strNum[CALCSIZE];
int strNumCount = 0;
float tempNum = -1;
bool isNegative = false, isUnaryNot = false, decPoint = false;
static float decimalMul = 1;

// initialize value storages! (a-z, A-Z) -> (1-26, 27-52)
#define STO_SIZE 51
static float valStorage[STO_SIZE];

// Must be called before calc is used!
void initialize_calc() {
    memset(valStorage, 0, STO_SIZE);
}

static void __resetDecimals() {
    decPoint = false;
    decimalMul = 1;
}

// concatinating for calculator
float concat(float x, float y)
{
    if(x < 0) {
        return y;
    }
    if(y < 0) {
        return x;
    }
    if (!decPoint) {
        int pow = 10;
        while(y >= pow) pow *= 10;
        return x * pow + y;
    }
    decimalMul *= 0.1;
    return x + y * decimalMul;
}

bool isMathOperator(char charToCheck) {
    return charToCheck == '+' || charToCheck == '-' || charToCheck == '*' || charToCheck == '/' || charToCheck == '%' || charToCheck == '&' || charToCheck == '|' || charToCheck == '^' || charToCheck == '~' || charToCheck == '<' || charToCheck == '>' || charToCheck == '=' || charToCheck == '[' || charToCheck == ']' || charToCheck == ':';
}

void calcHelp()
{
    printint(mathOp[0], 0x0F);
    print("\nCalculator help: ", 0x0F);
    print("\n[HELP TEXT HERE]", 0x0F);
}

void resetVar() {
    //Reset operational variable to its default state
    memset(calcInput, '\0', CALCSIZE);
    memset(mathOp, '\0', CALCSIZE);
    memset(strNum, '\0', CALCSIZE);
    tempNum = -1;
    strNumCount = 0;
    isNegative = false;
    isUnaryNot = false;
    __resetDecimals();
}

//Prints an error based on the error ID
void mathError(uint8 ID)
{
    newline();

    //Because if the program terminates prematurly, it cannot call resetVar()
    //So, if program terminates prematurly, call it here...
    resetVar();

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
    else if(strEql(args," -y"))
    {
       //getTime() test
       printint(getTime("year"),0x0F);
    }
    else if(strEql(args," -pi"))
    {
        newline();
        print(PI_S, 0x08);
    }
    else if(strEql(args," -e"))
    {
        newline();
        print(E_S, 0x08);
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
    else if(strEql(args, " -list"))//For testing lists
    {
        newline();
        list_t test_list = list_init();
        test_list.autoShrink = true;
        list_add(&test_list, "1");
        list_add(&test_list, "2");
        list_add(&test_list, "3");
        list_add(&test_list, "4");
        list_add(&test_list, "5");
        list_add(&test_list, "6");
        list_add(&test_list, "7");
        list_add(&test_list, "8");
        list_add(&test_list, "9");
        list_add(&test_list, "10");
        list_add(&test_list, "11");
        list_add(&test_list, "12");
        list_add(&test_list, "13");
        list_add(&test_list, "14");
        list_add(&test_list, "15");
        list_add(&test_list, "16");

        list_add(&test_list, "1");
        list_add(&test_list, "2");
        list_add(&test_list, "3");
        list_add(&test_list, "4");
        list_add(&test_list, "5");
        list_add(&test_list, "6");
        list_add(&test_list, "7");
        list_add(&test_list, "8");
        list_add(&test_list, "9");
        list_add(&test_list, "10");
        list_add(&test_list, "11");
        list_add(&test_list, "12");
        list_add(&test_list, "13");
        list_add(&test_list, "14");
        list_add(&test_list, "15");
        list_add(&test_list, "16");

        list_add(&test_list, "1");
        list_add(&test_list, "2");
        list_add(&test_list, "3");
        list_add(&test_list, "4");
        list_add(&test_list, "5");
        list_add(&test_list, "6");
        list_add(&test_list, "7");
        list_add(&test_list, "8");
        list_add(&test_list, "9");
        list_add(&test_list, "10");
        list_add(&test_list, "11");
        list_add(&test_list, "12");
        list_add(&test_list, "13");
        list_add(&test_list, "14");
        list_add(&test_list, "15");
        list_add(&test_list, "16");

        list_add(&test_list, "1");
        list_add(&test_list, "2");
        list_add(&test_list, "3");
        list_add(&test_list, "4");
        list_add(&test_list, "5");
        list_add(&test_list, "6");
        list_add(&test_list, "7");
        list_add(&test_list, "8");
        list_add(&test_list, "9");
        list_add(&test_list, "10");
        list_add(&test_list, "11");
        list_add(&test_list, "12");
        list_add(&test_list, "13");
        list_add(&test_list, "14");
        list_add(&test_list, "15");
        list_add(&test_list, "16");

        println("Done sizing up", 0x0F);
        printint(test_list.capt, 0x0f);

        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);
        list_shift(&test_list);

        newline();
        println("Removed all items from test_list", 0x0F);
        for(uint8 i = 0; i < test_list.size; i++)
            println(test_list.data[i], 0x0F);
        println("Done sizing up", 0x0F);
        printint(test_list.capt, 0x0f);
        
        list_destroy(&test_list);
    }
    else
    {
        print("\nUse calc -h for help\n>  ", 0x0F);
        memset(calcInput, '\0', CALCSIZE);
        readStr(calcInput, CALCSIZE);
        strcat(calcInput, "+0"); // Unary related hack! do not delete

        for(int i = 0; i < CALCSIZE; i++)
        {
            if((calcInput[i] == 0) || (calcInput[i] == 10))
                break;
            else
            {
                int pInput = ntoi(calcInput[i]);
                if (pInput != -1)
                    tempNum = concat(tempNum, pInput);
                else if (calcInput[i] == '.') {
                    decPoint = true;
                } else if (isalpha(calcInput[i])) {
                    __resetDecimals();
                    int valIndex = ctoi(calcInput[i]) - 10; // [0-9], [a-z], [A-Z], +, /
                    tempNum = concat(tempNum, valIndex);
                    print("\nVar: ", 0x0f);
                    printint(valStorage[valIndex], 0x0f);
                } else {
                    __resetDecimals();
                    // Properly check for math operator
                    if(isMathOperator(calcInput[i])) {
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
                                tempNum = ~((int) tempNum);
                            strNum[strNumCount] = tempNum;
                            mathOp[strNumCount++] = calcInput[i]; 	// set math operator
                            tempNum = -1;
                            isNegative = false;
                            isUnaryNot = false;
                            __resetDecimals();
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
            else if(mathOp[i] == '=')
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
                }else{
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
            }
            else if(mathOp[i] == '%')
            {
                if(strNum[i+1] == 0)
                {
                    mathError(1);
                    return;
                }else{
                  strNum[i] = ((int) strNum[i]) % ((int) strNum[i+1]);
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

        //Then do '[' and ']' (Bitshifts)
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == '[') // Shift to right
            {
                strNum[i] = ((int) strNum[i]) << ((int) strNum[i+1]);
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
            else if(mathOp[i] == ']') // Shift to left
            {
                strNum[i] = ((int) strNum[i]) >> ((int) strNum[i+1]);
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
                strNum[i] = ((int) strNum[i]) & ((int) strNum[i+1]);
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
                strNum[i] = ((int) strNum[i]) | ((int) strNum[i+1]);
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
                strNum[i] = ((int) strNum[i]) ^ ((int) strNum[i+1]);
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

        // ':' the assign operator
        for(int i = 0; i < strNumCount-1;i++) {
            if(mathOp[i] == ':')
            {
                valStorage[(int) strNum[i-1]] = strNum[i+1];
                strNum[i] = strNum[i+1]; // Resume tail expressions
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
        printfloat(strNum[0], 0x0F);

        //Reset operational variable to its default state
        resetVar();
    }
}
