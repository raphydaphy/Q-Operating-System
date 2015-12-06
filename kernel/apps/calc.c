#include "calc.h"

#define CALC_SIZE 128
static char calcInput[CALC_SIZE];

// Must be called before calc is used!
inline void initialize_calc() {
    memset(calcInput, 0, CALC_SIZE);
}

typedef enum {
    NOOP = 0, // Similar to default state
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
    ILLEGAL = -1
} legalOps;

static inline legalOps getOperator(char charToCheck) {
    switch(charToCheck) {
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
    default: return ILLEGAL;
    }
}

void calcHelp()
{
    print("\nCalculator help: ", 0x0F);
    print("\n[HELP TEXT HERE]", 0x0F);
}

//Prints an error based on the error ID
void mathError(mathExcept ID)
{
    switch (ID) {
    case START_W_OP:
        print("Cannot start with an operator", 0x04);
        break;
    case DIV_BY_ZERO:
        print("Cannot divide by 0", 0x04);
        break;
    case ILLEGAL_OP:
        print("Illegal operator found", 0x04);
        break;
    case OTHER:
        print("Unknown math exception: ", 0x04);
        printint(ID, 0x04);
        break;
    }
    newline();
}

void calc(string args)
{
    initialize_calc();
    if(streql(args," -h"))
       calcHelp();
    else if(streql(args," -pi"))
    {
        newline();
        print(PI_S, 0x08);
    }
    else if(streql(args," -e"))
    {
        newline();
        print(E_S, 0x08);
    }
    else if(streql(args," -pow"))
    {
        newline();
        print("Number>  ",0x08);
        readStr(calcInput, CALC_SIZE);
        newline();
    	printfloat(powerOfTen(stoi(calcInput)), 0x0F);
    }
    else if(streql(args," -sin"))
    {
        newline();
        print("Angle in gradiant>  ",0x08);
        readStr(calcInput, CALC_SIZE);
        newline();
    	printfloat(sin(stoi(calcInput)), 0x0F);
    }
    else if(streql(args," -cos"))
    {
        newline();
        print("Angle in gradiant>  ",0x08);
        readStr(calcInput, CALC_SIZE);
        newline();
    	printfloat(cos(stoi(calcInput)), 0x0F);
    }
    else
    {
        strbuilder_t simStack = strbuilder_init();
        print("\nUse calc -h for help\n>  ", 0x0F);
        readStr(calcInput, CALC_SIZE);
        strbuilder_append(&simStack, "0+"); // "Evaluate" related hack!
        strbuilder_append(&simStack, calcInput);
        newline();
        printfloat(calc_parse(simStack), 0x08);
        strbuilder_destroy(&simStack);
    }
}

float calc_parse(strbuilder_t txt) {
    strbuilder_trim(&txt);
    char c = 0;
    list_t opStack = list_init();
    strbuilder_t buffer = strbuilder_init();
//    legalOps prev = NOOP; // This used to check for <<, <=, and such
    for(uint32 i = 0; i < txt.size; i++) {
        c = strbuilder_charAt(txt, i);
        // Tokenize!
        if(isnum(c) || c == '.') {
            strbuilder_appendc(&buffer, c);
        } else {
            if(isspace(c)) {
                continue;
            } else {
                legalOps cop = getOperator(c);
                if (cop == ILLEGAL) {
                    mathError(ILLEGAL_OP);
                    return 0;
                }
                // Push number in stack
                if (strbuilder_head(buffer) == '.') {
                    string tail = strbuilder_clear(&buffer);
                    strbuilder_appendc(&buffer, '0');
                    strbuilder_append(&buffer, tail);
                }
                if (strbuilder_tail(buffer) == '.') {
                    strbuilder_appendc(&buffer, '0');
                }
                list_add(&opStack, strbuilder_tostr(buffer));
                strbuilder_clear(&buffer);
                // Push operator in stack
                list_addi(&opStack, cop);
                //prev = cop;
            }
        }
    }
    // Add the last couple numbers
    list_add(&opStack, strbuilder_tostr(buffer));
    strbuilder_clear(&buffer);

    return evaluate(opStack);
}

#define __testDivByZero(right) \
    if(right == 0) { \
        mathError(DIV_BY_ZERO); \
        return left; \
    } \

#define __assign(v) \
    float val = v; \
    if (!lvalid) { \
        left = val; \
        lvalid = true; \
    } else { \
        right = val; \
        switch(procop) { \
        case ADD: \
            left += right; \
            break; \
        case SUB: \
            left -= right; \
            break; \
        case MUL: \
            left *= right; \
            break; \
        case DIV: \
            __testDivByZero(right); \
            left /= right; \
            break; \
        case MOD: \
            __testDivByZero(right); \
            left = ((int) left) % ((int) right); \
            break; \
        case BIT_AND: \
            left = ((int) left) & ((int) right); \
            break; \
        case BIT_OR: \
            left = ((int) left) | ((int) right); \
            break; \
        case BIT_XOR: \
            left = ((int) left) ^ ((int) right); \
            break; \
        default: \
            break; \
        } \
    }

float evaluate(list_t opStack) {
    // Evaluate
    bool lvalid = false;
    float left = 0, right = 0;
    legalOps procop = NOOP;
    for(uint32 i = 0; i < opStack.size; i++) {
        if (list_getType(opStack, i) == STR) {
            string tmp = list_get(opStack, i);
            __assign(stod(tmp));
        } else {
            legalOps test = list_geti(opStack, i);
            if (test == RPAREN) {
                uint32 oldPos = i;
                uint32 nestLvl = 0;
                nestLvl++;
                while (nestLvl > 0) {
                    test = list_geti(opStack, ++i);
                    if (test == RPAREN) nestLvl++;
                    else if (test == LPAREN) nestLvl--;
                }
                list_t nopstc = list_sublist(opStack, oldPos + 1, i);
                __assign(evaluate(nopstc));
                list_destroy(&nopstc);
            } else {
                procop = test;
            }
        }
    }
    return left;
}

