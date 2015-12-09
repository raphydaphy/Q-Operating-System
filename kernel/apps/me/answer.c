#include "answer.h"

string answer(string question, uint8 offset)
{
    if (streql(question,"exit"))
    {
        querying = false;
        return "Terminated by User.";
    }
    else
    {
        bool over = false;
        int tmp = offset;

        newline();

        while (!over)
        {
            if (streql(splitArg(question, tmp),""))
            {
                over = true;
            }
            else
            {
                print(" | ",green);
                print(toUpper(splitArg(question, tmp)),magenta);
                print(" ",magenta);
                print(sort(splitArg(question, tmp)),magenta);
            }
            tmp++;
        }

        return "Not Terminated.";
    }
}
