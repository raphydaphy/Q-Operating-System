//This file just has two simple functions to compare two strings and to get the length of a string

ifndef STRING_H
#define STRING_H

uint16 strlength(string ch)
{
        uint16 i = 1;
        while(ch[i++]);  
        return --i;
}

/*This function compares two strings and returns true (1) if they are equal or false (0) if they are not equal */

uint8 strEql(string ch1,string ch2)                     
{
        uint8 result = 1;
        uint8 size = strlength(ch1);
        if(size != strlength(ch2)) result =0;
        else 
        {
        uint8 i = 0;
        for(i;i<=size;i++)
        {
                if(ch1[i] != ch2[i]) result = 0;
        }
        }
        return result;
}


#endif

