#include "kbDetect.h"

const char kbLowerChars[256] =    {
     0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=',  0 ,'\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0 ,  0 ,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
   '\'', '`',  0 ,'\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,
};

const char kbShiftChars[256] =    {
     0 ,  0 , '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '_', '+',  0 ,'\t', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',  0 ,  0 ,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
   '\"', '~',  0 , '|', 'Z', 'X', 'C', 'V', 'B', 'N',
    'M', '<', '>', '?',  0 , '*',  0 , ' ',  0 ,
};

void kbHelp()
{
    print("\nKeybindings in Q OS:", white);
    print("\n\tCtrl-b -> left", white);
    print("\n\tCtrl-f -> right", white);
    print("\n\tCtrl-a -> home", white);
    print("\n\tCtrl-p -> up", white);
    print("\n\tCtrl-n -> down", white);
    print("\n\tCtrl-z -> quit", white);
    println("\n\tCtrl-l -> clear", white);
}
