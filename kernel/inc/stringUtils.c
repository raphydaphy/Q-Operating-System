#include "stringUtils.h"

uint16 strlength(string ch)
{
    uint16 i = 0;
    while(ch[++i]);  
    return i;
}

bool strEql(string ch1,string ch2)                     
{
    uint16 i = 0;
    while(ch1[i] && ch2[i]) {
        if(ch1[i] != ch2[i]) {
            return false;
        }
        i++;
    }
    return true;
}

bool isspace(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\f' || ch == '\0')
        return true;
    return false;
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

    len = strlength(str);
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
/*Sets content of a string*/
void strSet(string target, string source) {
    int i = 0;
    while(source[i]) {
        target[i] = source[i];
        i++;
    }
    target[i] = 0;
}
