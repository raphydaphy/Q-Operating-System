#include "calc.h"

#define CALC_SIZE 128
static char calcInput[CALC_SIZE];

// There are 52 alphabets
static float varList[52];

static hashmap_t funcList;

// Must be called before calc is used!
inline void initialize_calc()
{
    memset(varList, 0, 50);
    funcList = hashmap_init();
}

typedef enum
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    MOD = 5,
    RPAREN = 6,
    LPAREN = 7,
    BIT_AND = 8,
    BIT_OR = 9,
    BIT_XOR = 10,
    LESSER_T = 11,
    GREATER_T = 12,
    EQUALS_T = 13,
    ASSIGN = 14,
    ROUND = 15,
    // Here beyond are special ops
    // that are two chars in length
    NOOP = 0, // Similar to default state
    ILLEGAL = -1, // Bad operator
    SHIFT_L = -2, // <<
    SHIFT_R = -3, // >>
    LESS_EQ = -4, // <=
    GREAT_EQ = -5 // >=
} legalOps;

static inline legalOps getOperator(char charToCheck)
{
    switch(charToCheck)
    {
    case '+': return ADD;
    case '-': return SUB;
    case '*': return MUL;
    case '/': return DIV;
    case '%': return MOD;
    case '(': return RPAREN;
    case ')': return LPAREN;
    case '&': return BIT_AND;
    case '|': return BIT_OR;
    case '^': return BIT_XOR;
    case '<': return LESSER_T;
    case '>': return GREATER_T;
    case '=': return EQUALS_T;
    case ':': return ASSIGN;
    case '$': return ROUND;
    default: return ILLEGAL;
    }
}

void calcHelp()
{
    print("\nCalculator help:", white);
    print("\ncalc [OPTIONS] | <expr>", white);
    print("\nOPTIONS:", white);
    print("\n\t-h", white);
}

//Prints an error based on the error ID
void mathError(mathExcept ID)
{
    switch (ID)
    {
    case START_W_OP:
        print("Cannot start with an operator", red);
        break;
    case DIV_BY_ZERO:
        print("Cannot divide by 0", red);
        break;
    case ILLEGAL_OP:
        print("Illegal operator found", red);
        break;
    case OTHER:
        print("Unknown math exception: ", red);
        printint(ID, red);
        break;
    }
    newline();
}

void calc(string args)
{
    if(streql(splitArg(args, 1), "") || streql(splitArg(args, 1), "-h"))
    {
       calcHelp();
    }
    else if(streql(splitArg(args, 1), "-pow"))
    {
        newline();
        print("Number>  ",dark_grey);
        readStr(calcInput, CALC_SIZE,false);
        newline();
    	printfloat(powerOfTen(stoi(calcInput)), white);
    }
    else
    {
        memset(calcInput, 0, CALC_SIZE);
        strbuilder_t simStack = strbuilder_init();
        bool complete = false;
        int cpyCount = 1;

        strcpy(calcInput,splitArg(args, 1));

        while (!complete)
        {
            cpyCount++;
            if (streql(splitArg(args, cpyCount),"") || streql(splitArg(args, cpyCount)," "))
            {
                complete = true;
            }
            else
            {
                strcat(calcInput,splitArg(args, cpyCount));
            }
        }

        if (strTrim(calcInput)[0] == '(')
        {
            // This relates to when brackets is the first term of the expr
            strbuilder_append(&simStack, "1"); // (3) := 0; 1(3) := 3
        }
        strbuilder_append(&simStack, calcInput);
        newline();
        printfloat(calc_parse(simStack), white);
        strbuilder_destroy(&simStack);
    }
}

float calc_parse(strbuilder_t txt)
{
    strbuilder_trim(&txt);
    char c = 0;
    list_t opStack = list_init();
    strbuilder_t buffer = strbuilder_init();
    legalOps prev = NOOP; // This used to check for <<, <=, and such
    for(uint32 i = 0; i < txt.size; i++)
    {
        c = strbuilder_charAt(txt, i);
        // Tokenize!
        if(isnum(c) || c == '.')
        {
            prev = NOOP;
            strbuilder_appendc(&buffer, c);
        }
        else
        {
            if(isspace(c))
            {
                prev = NOOP;
            }
            else if (isalpha(c))
            {
                list_addc(&opStack, c); // Variables! Yay
            }
            else if (c == '[')
            {
                // (4.5)[ceil] := (4.5)[ ceil ]
                // Note `[`, `]` cannot be part a function name
                uint32 endFunc = strbuilder_indexOf(txt, "]");
                list_add(&opStack, strbuilder_substr(txt, i, endFunc));
                i = endFunc;
            }
            else if (c == '{')
            {
                // A square function would be like this: {_*_}[square]
                uint32 endFunc = strbuilder_indexOf(txt, "]");
                list_add(&opStack, strbuilder_substr(txt, i, endFunc));
                i = endFunc;
            }
            else
            {
                legalOps cop = getOperator(c);
                if (cop == ILLEGAL)
                {
                    mathError(ILLEGAL_OP);
                    return 0;
                }
                if (prev == LESSER_T)
                {
                    if (cop == LESSER_T)
                    {
                        cop = SHIFT_L;
                    }
                    if (cop == EQUALS_T)
                    {
                        cop = LESS_EQ;
                    }
                }
                if (prev == GREATER_T)
                {
                    if (cop == GREATER_T)
                    {
                        cop = SHIFT_R;
                    }
                    if (cop == EQUALS_T)
                    {
                        cop = GREAT_EQ;
                    }
                }
                // Push number in stack
                if (strbuilder_head(buffer) == '.')
                {
                    string tail = strbuilder_clear(&buffer);
                    strbuilder_appendc(&buffer, '0');
                    strbuilder_append(&buffer, tail);
                }
                if (strbuilder_tail(buffer) == '.')
                {
                    strbuilder_appendc(&buffer, '0');
                }
                list_add(&opStack, strbuilder_tostr(buffer));
                strbuilder_clear(&buffer);
                // Push operator in stack
                list_addi(&opStack, cop);
                prev = cop;
            }
        }
    }
    // Add the last couple numbers
    list_add(&opStack, strbuilder_tostr(buffer));
    strbuilder_destroy(&buffer);
    for(uint32 i = 0; i < opStack.size; i++)
    {
        if (list_getType(opStack, i) == INT)
        {
            if(list_geti(opStack, i) < 0)
            {
                // Remove extra bits '<<' := '<', '<<'
                list_remove(&opStack, i - 2);
            }
        }
    }
    return evaluate(opStack);
}

#define __testDivByZero(right) \
    if(right == 0) \
    { \
        mathError(DIV_BY_ZERO); \
        return; \
    }

static void __assign(float value, bool* lvalid, float* left, float* right, legalOps procop, uint8 spot) {
    float val = value;
    if (val == 0 && spot < 53 && procop != ASSIGN)
    {
        val = varList[spot];
    }
    if (!*lvalid) {
        *left = val;
        *lvalid = true;
    }
    else
    {
        *right = val;
        switch(procop)
        {
        case ADD:
            *left += *right;
            break;
        case SUB:
            *left -= *right;
            break;
        case MUL:
            *left *= *right;
            break;
        case DIV:
            __testDivByZero(*right);
            *left /= *right;
            break;
        case MOD:
            __testDivByZero(*right);
            *left = ((int) *left) % ((int) *right);
            break;
        case BIT_AND:
            *left = ((int) *left) & ((int) *right);
            break;
        case BIT_OR:
            *left = ((int) *left) | ((int) *right);
            break;
        case BIT_XOR:
            *left = ((int) *left) ^ ((int) *right);
            break;
        case SHIFT_L:
            *left = ((int) *left) << ((int) *right);
            break;
        case SHIFT_R:
            *left = ((int) *left) >> ((int) *right);
            break;
        case LESSER_T:
            *left = *left < *right;
            break;
        case GREATER_T:
            *left = *left > *right;
            break;
        case EQUALS_T:
            *left = *left == *right;
            break;
        case LESS_EQ:
            *left = *left <= *right;
            break;
        case GREAT_EQ:
            *left = *left >= *right;
            break;
        case ASSIGN:
            varList[spot] = *left;
            break;
        case ROUND:
            *left = round(*left);
            break;
        default:
            break;
        }
    }
}

static inline string __extractFuncName(strbuilder_t* strb, string rawName)
{
    strbuilder_clear(strb);
    strbuilder_append(strb, rawName);
    strbuilder_trim(strb);
    strbuilder_rmOuter(strb, 1, 1);
    strbuilder_trim(strb);
    return strbuilder_tostr(*strb);
}

float evaluate(list_t opStack)
{
    bool lvalid = false;
    float left = 0, right = 0;
    legalOps procop = NOOP;
    for(uint32 i = 0; i < opStack.size; i++)
    {
        if (list_getType(opStack, i) == STR)
        {
            string tmp = list_get(opStack, i);
            strbuilder_t funcName = strbuilder_init();
            if (tmp[0] == '[')
            {
                string fname = __extractFuncName(&funcName, tmp);
                if(streql(fname, "ceil"))
                {
                    left = ceil(left);
                }
                else if(streql(fname, "floor"))
                {
                    left = floor(left);
                }
                else if(streql(fname, "round"))
                {
                    left = round(left);
                }
                else if(streql(fname, "Pi"))
                {
                    // Type casting twice because Pi is way Out of range
                    // If we use (float)PI, we loose accuracy
                    __assign(stod(ftos(PI)), &lvalid, &left, &right, procop, 53);
                }
                else if(streql(fname, "e"))
                {
                    // Same as [Pi]
                    __assign(stod(ftos(E)), &lvalid, &left, &right, procop, 53);
                }
                else if(streql(fname, "sin"))
                {
                    left = sin(left);
                }
                else if(streql(fname, "cos"))
                {
                    left = cos(left);
                }
                else if(streql(fname, "sec"))
                {
                    left = 1.0 / cos(left);
                }
                else if(streql(fname, "csc"))
                {
                    left = 1.0 / sin(left);
                }
                else if(streql(fname, "tan"))
                {
                    left = sin(left) / cos(left);
                }
                else if(streql(fname, "sqrt"))
                {
                    left = sqrt(left);
                }
                else if(streql(fname, "cbrt"))
                {
                    left = cbrt(left);
                }
                else
                {
                    string rInput = etos(hashmap_getVal(funcList, fname));
                    if(streql(rInput, ""))
                    {
                        print("Cannot find macro: ", red);
                        println(fname, red);
                    }
                    else
                    {
                        strbuilder_t simStack = strbuilder_init();
                        if (strTrim(rInput)[0] == '(')
                        {
                            // This relates to when brackets is the first term of the expr
                            strbuilder_append(&simStack, "1"); // (3) := 0; 1(3) := 3
                        }
                        strbuilder_append(&simStack, rInput);
                        // Must replace `_` with value left
                        println(strbuilder_tostr(simStack), red);
                        __assign(calc_parse(simStack), &lvalid, &left, &right, procop, 53);
                        strbuilder_destroy(&simStack);
                    }
                }
            } else if (tmp[0] == '{')
            {
                strbuilder_append(&funcName, tmp);
                uint32 endFunc = strbuilder_indexOf(funcName, "}");
                string fbody = strbuilder_substr(funcName, 1, endFunc);
                string fname = strbuilder_substr(funcName, endFunc + 1, funcName.size);
                fname = __extractFuncName(&funcName, fname);

                print(fname, dark_grey);
                print("->", dark_grey);
                print(fbody, dark_grey);
                newline();

                hashmap_add(&funcList, fname, makeStrElement(fbody));
            }
            else
            {
                __assign(stod(tmp), &lvalid, &left, &right, procop, 53);
            }
            strbuilder_destroy(&funcName);
        }
        else if (list_getType(opStack, i) == CHR)
        {
            float tmp = ctoi(list_getc(opStack, i)) - 10;
            __assign(0, &lvalid, &left, &right, procop, tmp);
        }
        else
        {
            legalOps test = list_geti(opStack, i);
            if (test == RPAREN)
            {
                uint32 oldPos = i;
                uint32 nestLvl = 0;
                nestLvl++;
                while (nestLvl > 0)
                {
                    if(opStack.size > i + 1)
                    {
                        test = list_geti(opStack, ++i);
                        if (test == RPAREN)
                        {
                            nestLvl++;
                        }
                        else if (test == LPAREN)
                        {
                            nestLvl--;
                        }
                    }
                    else
                    {
                        nestLvl = 0; // Assume the user forgot a bracket
                        i++;
                    }
                }
                list_t nopstc = list_sublist(opStack, oldPos + 1, i);
                __assign(evaluate(nopstc), &lvalid, &left, &right, procop == NOOP ? MUL : procop, 53);
                list_destroy(&nopstc);
            }
            else
            {
                procop = test;
            }
        }
    }
    return left;
}
