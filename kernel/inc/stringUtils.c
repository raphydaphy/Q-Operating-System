#include "stringUtils.h"
#include "kheap.h" // THIS LINE MUST BE HERE!!!

uint16 strlen(string ch)
{
    uint16 i = 0;
    while(ch[++i]);
    return i;
}

bool streql(string ch1,string ch2)
{
    /* Zero from strcmp means ch1 eq ch2 */
    return strcmp(ch1, ch2) == 0;
}

// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
uint8 strcmp(string str1, string str2)
{
    int i = 0;
    int failed = 0;
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] != str2[i])
        {
            failed = 1;
            break;
        }
        i++;
    }
    // why did the loop exit?
    if((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
        failed = 1;
    return failed;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
string strcpy(string dest, string src)
{
    do
      *dest++ = *src++;
    while (*src != 0);
    return dest;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
string strcat(string dest, string src)
{
    while (*dest != 0) {
        *dest = *dest;
        dest++;
    }

    do
        *dest++ = *src++;
    while (*src != 0);
    return dest;
}

string append(string dest, char src)
{
    while (*dest != 0) {
        *dest = *dest;
        dest++;
    }
    *dest = src;
    return dest;
}

string strTrim(string str)
{
    uint16 len = 0;
    string frontp = str;
    string endp = 0;

    if(str == 0)
        return 0;
    if(str[0] == '\0')
        return str;

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while(isspace(*frontp))
        ++frontp;
    if(endp != frontp)
    {
        while(isspace(*(--endp)) && endp != frontp) {}
    }

    if(str + len - 1 != endp)
        *(endp + 2) = '\0';
    else if(frontp != str && endp == frontp)
        *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if(frontp != str)
    {
        while(*frontp)
            *endp++ = *frontp++;
        *endp++ = '\0';
    }

    return str;
}

#define INT_DIGITS 19       /* enough for 64 bit integer */

/*
 * Based off itoa from opensource apple com.
 */
string itos(int i, uint8 base) {
    /* Room for INT_DIGITS digits, - and '\0' */
    static char buf[INT_DIGITS + 2];
    string p = buf + INT_DIGITS + 1;  /* points to terminating '\0' */
    bool isNeg = false;
    if (i < 0) {
        isNeg = true;
        i = -i;
    }
    do {
        *--p = itoc(i % base);
        i /= base;
    } while (i != 0);
    if (isNeg) {
        *--p = '-';
    }
    return p;
}

#define FLOAT_DIGITS INT_DIGITS * 2

string ftos(float f) {
    // Room for the digits, -, '\0', '.'
    static char buf[FLOAT_DIGITS + 3];
    string p = buf + FLOAT_DIGITS + 1;  /* points to terminating '\0' */
    memset(p, 0, FLOAT_DIGITS + 3);
    int i = (int) f;
    f -= i;
    strcat(p, itos10(i));
    strcat(p, ".");
    f = abs(f); // Clear negativity
    while(((int) f) != f) {
        // Pad zeros
        f *= 10;
    }
    strcat(p, itos10((int) f));
    return p;
}

string get0Arg(string rawArgs)
{
    bool zeroArgGenOver = false;
    string curArg = (string) kmalloc(10 * sizeof(char));
    string zeroArg = rawArgs;

    uint16 tmp = 0;
    uint16 modTmp = (tmp + 1);
    while (!zeroArgGenOver && modTmp < arrLength(rawArgs))
    {
        modTmp = tmp + 1;

        // For Debug:
        //printint(tmp,0x03);

        char curArgChar = rawArgs[tmp];
        char curArgCharString[] = { curArgChar, '\0' };

        if (streql(curArgCharString," "))
        {
            zeroArgGenOver = true;
            memset(curArg, '\0', 128);
            zeroArg = curArg;
            kfree(curArg);
            return zeroArg;
        }
        else
        {
            print(curArgCharString,0x0F);
            strcat(curArg,curArgCharString);
        }

        tmp++;
    }

    kfree(curArg);
    return zeroArg;
}

static int convValidate;

int stoi(string s)
{
    int msg = 0;
    bool hasN = false;
    uint16 i = 0;
    if (s[0] == '-') {
        hasN = true;
        i++;
    }
    while(s[i]) {
        msg *= 10;
        convValidate = ntoi(s[i]);
        if(convValidate == -1) break;
        msg += convValidate;
        i++;
    }
    if (hasN) msg = -msg;
    return msg;
}

int htoi(string s)
{
    int msg = 0;
    bool hasN = false;
    uint16 i = 0;
    if (s[0] == '-') {
        hasN = true;
        i++;
    }
    while(s[i]) {
        msg *= 10;
        convValidate = ctoi(s[i]);
        if(convValidate == -1) break;
        msg += convValidate;
        i++;
    }
    if (hasN) msg = -msg;
    return msg;
}

uint32 stoc(string str) {
    uint32 msg = 0;
    do
      msg += abs(*str++);
    while (*str != 0);
    return msg;
}

double stod(string s)
{
    double fmp = 1;
    double msg = 0.0;
    bool hasDec = false;
    bool hasN = false;
    uint16 i = 0;
    if (s[0] == '-') {
        hasN = true;
        i++;
    }
    while(s[i]) {
        if (isnum(s[i])) {
            if (hasDec) {
                fmp *= 0.1;
                msg += ntoi(s[i]) * fmp;
            } else
                msg = msg * 10 + ntoi(s[i]);
        } else if (s[i] == '.') {
            if (hasDec) break;
            hasDec = true;
        } else break;
        i++;
    }
    if (hasN) msg = -msg;
    return msg;
}

string splitArg(string args, int argc) {// argc is the argument the program needs (argument n)
    int i = 0;
    int j = 0;
    int argLoc = 0;

    static char fargs[1028];
    memset(fargs, 0, 1028);
    while(args[i] != 0 && args[i] != 10) {
		if(args[i] == 32) {
	    	argLoc += 1;
		}
		if(argLoc == argc) {
		    while(args[i+j+1] != 32 && args[i+j+1] != 0) {
				fargs[j] = args[i+j+1];
				j++;
			}
	    	break;
		}
		i++;
    }
    i = 0;
    j = 0;

    return fargs;
}

string sentenceCase(string s) {
    s[0] = toUpperC(s[0]);
    uint16 i = 1;
    while(s[i]) {
        s[i] = toLowerC(s[i]);
        i++;
    }
    return s;
}

string toUpper(string s) {
    uint16 i = 0;
    while(s[i]) {
        s[i] = toUpperC(s[i]);
        i++;
    }
    return s;
}

string toLower(string s) {
    uint16 i = 0;
    while(s[i]) {
        s[i] = toLowerC(s[i]);
        i++;
    }
    return s;
}
