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

int convertBase(int num, int baseEnd, int baseStart = 10)
{
    //Reserved for Raph
    /*
        Notes from Patrick:
        You need to have both a start base and an end base.
        You can assume if the start base is missing that its base10.
        You will need to convert from baseStart => base10 => baseEnd
        You will need a catalog of all digits. These will need to be characters. This is needed if you want to go higher than base 10. If you use the Alphabet, then you can go up to base36.
        The start number and the end number will need to be strings instead of integers if we want to go higher than base10.
        I wrote a Base converter a few months ago in JavaScript: https://www.khanacademy.org/cs/base-to-base-number-converter/6447800689885184
    */
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

