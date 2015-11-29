#include "charUtils.h"

#define IN_RANGE(val, low, high) ((val >= low) && (val <= high))

inline bool isspace(char ch) {
    return (ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n') || (ch == '\f') || (ch == '\0');
}

inline bool isnum(char ch) {
    return IN_RANGE(ch, '0', '9');
}

inline bool isalpha(char ch) {
    return islower(ch) || isupper(ch);
}

inline bool islower(char ch) {
    return IN_RANGE(ch, 'a', 'z');
}

inline bool isupper(char ch) {
    return IN_RANGE(ch, 'A', 'Z');
}

inline bool isword(char ch) {
    return isalpha(ch) || isnum(ch) || ch == '_';
}

int ctoi(char c)
{
    if (isnum(c))
        return c - '0';
    else if (islower(c))
        return c - 'a' + 10;
    else if (isupper(c))
        return c - 'A' + 36;
    else if (c == '+')
        return 62;
    else if (c == '/')
        return 63;
    return -1;
}

int ntoi(char c)
{
    if (isnum(c))
        return c - '0';
    return -1;
}

char itoc(int i) {
    if (IN_RANGE(i, 0, 9))
        return i + '0';
    else if (IN_RANGE(i, 10, 35))
        return i - 10 + 'a'; // Use lowercase for hex digits
    else if (IN_RANGE(i, 36, 61))
        return i - 36 + 'A'; // Use UPPERCASE for higher encoding digits
    else if (i == 62)
        return '+';
    else if (i == 63)
        return '/';
    return '\0';
}

const char caseThersold = 'a' - 'A';

char toLowerC(char c) {
    if (isupper(c)) {
        c += caseThersold; // Difference between 'A'(65) and 'a'(97)
    }
    return c;
}

char toUpperC(char c) {
    if (islower(c)) {
        c -= caseThersold; // Difference between 'A'(65) and 'a'(97)
    }
    return c;
}

