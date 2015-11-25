#include "math.h"

double powerOfTen(int num){
   double rst = 1.0;
   if(num >= 0){
       for(int i = 0; i < num ; i++){
           rst *= 10.0;
       }
   }else{
       for(int i = 0; i < (0 - num ); i++){
           rst *= 0.1;
       }
   }
   return rst;
}

//double pow(double num, double){

//}

double squareRoot(double a)
{
   /*
         find more detail of this method on wiki methods_of_computing_square_roots
         *** Babylonian method cannot get exact zero but approximately value of the square_root
    */
    double z = a;
    double rst = 0.0;
    int max = 8;     // to define maximum digit
    int i;
    double j = 1.0;
    for(i = max ; i > 0 ; i--){
        // value must be bigger then 0
        if(z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0)
        {
            while( z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0)
            {
                j++;
                if(j >= 10) break;
            }
            j--; //correct the extra value by minus one to j
            z -= (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)); //find value of z

            rst += j * powerOfTen(i);     // find sum of a
            j = 1.0;


          }

     }

     for(i = 0 ; i >= 0 - max ; i--){
         if(z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0)
         {
             while( z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0)
             {
                 j++;
             }
             j--;
             z -= (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)); //find value of z

             rst += j * powerOfTen(i);     // find sum of a
             j = 1.0;
          }
     }
     // find the number on each digit
     return rst;
}

int convertBase10(int num, int base)
{
    print ("\nSetting Up Some Stuff...",0x0A);

    int sum = num/base;
    int rem = num%base;

    int curRem = rem;
    int curSum = sum;

    int result;

    unsigned join(unsigned x, unsigned y) {
        unsigned pow = 10;
        while(y >= pow)
            pow *= 10;
        return x * pow + y;
    }
    char digitConvert(int digit)
    {
        char charDigit = digit;
        printch(charDigit,0x0F);

        if (digit < 10)         { return charDigit; }
        else if (digit == 10)   { return 'A';       }
        else if (digit == 11)   { return 'B';       }
        else if (digit == 12)   { return 'C';       }
        else if (digit == 13)   { return 'D';       }
        else if (digit == 14)   { return 'E';       }
        else if (digit == 15)   { return 'F';       }
        else if (digit == 16)   { return 'G';       }
        else if (digit > base)  { return 'Z';       }
    }
    int compress(int curSum)
    {
        print("\nCompressing Stuff...",0x0B);

        curSum = curSum/base;
        curRem = curSum%base;

        curRem = digitConvert(curRem);
        result = join(curRem,result);
    }
    printch(digitConvert(8));
}


long round(double num)
{
    long res = (long) num;
    if ((num - res) >= 0.5) res++;
    return res;
}

long ceil(double num)
{
    long res = (long) num;
    if (num != res) res++;
    return res;
}

long floor(double num)
{
    long res = (long) num;
    if ((res < 0) && (num != res)) res--;
    return res;
}

double abs(double num)
{
    if (num < 0) return -num;
    return num;
}
