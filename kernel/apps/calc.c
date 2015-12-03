#include "calc.h"

// initialize the math storage variables
int mathOp[CALCSIZE];
list_t strNum = init_list();
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

static void __realign(int* i) {
    uint32 olds = strNum.size;
    list_remove(strNum, j);
    i--;
    for(int j = *i + 1; j < olds - 1; j++)
    {
        mathOp[j] = mathOp[j + 1];
    }
}

void calc(string args)
{
    memset(calcInput, '\0', CALCSIZE);
    if(strEql(args," -h"))
    {
       calcHelp();
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
    	printfloat(powerOfTen(stoi(calcInput)), 0x0F);
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
                                mathError(strNum.size == 0 ? 0 : 2);
                                return;
                            }
                        }
                        else
                        {
                            if(isNegative)
                                tempNum *= -1;
                            else if (isUnaryNot)
                                tempNum = ~((int) tempNum);
                            list_addi(&strNum, tempNum);
                            mathOp[strNum.size - 1] = calcInput[i]; 	// set math operator
                            tempNum = -1;
                            isNegative = false;
                            isUnaryNot = false;
                            __resetDecimals();
                        }
                    }
                }
            }
        }
        list_addi(&strNum, tempNum);
        static int i = 0;
        // '<' '>' and '='
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == '<')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) < list_getf(strNum, i + 1));
                __realign(&i);
            }
            else if(mathOp[i] == '>')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) > list_getf(strNum, i + 1));
                __realign(&i);
            }
            else if(mathOp[i] == '=')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) == list_getf(strNum, i + 1));
                __realign(&i);
            }
        }
        //'*' '/' and '%'
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == '*')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) * list_getf(strNum, i + 1));
                __realign(&i);
            }
            else if(mathOp[i] == '/')
            {
                if(list_getf(strNum, i + 1) == 0) {
                    mathError(1);
                    return;
                }
                list_replacef(&strNum, i, list_getf(strNum, i) / list_getf(strNum, i + 1));
                __realign(&i);
            }
            else if(mathOp[i] == '%')
            {
                if(list_getf(strNum, i + 1) == 0) {
                    mathError(1);
                    return;
                }
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) % ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
        }

        //Then do + and -
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == '+')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) + list_getf(strNum, i + 1));
                __realign(&i);
            }
            else if(mathOp[i] == '-')
            {
                list_replacef(&strNum, i, list_getf(strNum, i) - list_getf(strNum, i + 1));
                __realign(&i);
            }
        }

        //Then do '[' and ']' (Bitshifts)
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == '[') // Shift to right
            {
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) << ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
            else if(mathOp[i] == ']') // Shift to left
            {
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) >> ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
        }

        //Then do '&', '|', and '^'
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == '&')
            {
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) & ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
            else if(mathOp[i] == '|')
            {
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) | ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
            else if(mathOp[i] == '^')
            {
                list_replacef(&strNum, i, ((int) list_getf(strNum, i)) ^ ((int) list_getf(strNum, i + 1)));
                __realign(&i);
            }
        }

        // ':' the assign operator
        for(i = 0; i < strNum.size - 1;i++) {
            if(mathOp[i] == ':')
            {
                valStorage[(int) list_getf(strNum, i - 1)] = list_getf(strNum, i + 1);
                list_replacef(&strNum, i, list_getf(strNum, i + 1)); // Resume tail expressions
                __realign(&i);
            }
        }
        newline();
        printfloat(list_getf(strNum, 0), 0x0F);

        //Reset operational variable to its default state
        resetVar();
    }
}
