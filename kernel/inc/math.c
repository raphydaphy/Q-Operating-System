#include "math.h"

//CHRONO VARIABLES
//Time functions from http://wiki.osdev.org/CMOS
int century_register = 0x00;                                // Set by ACPI table parsing code if possible

#define CURRENT_YEAR 2015
unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;//Not the day of the week, but day of the month
unsigned char month;
unsigned int year;

//END CHRONO VARIABLES

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

double cbrt(double x) {
    if (x == 0) {
        return 0;
    }
    double b = 1; // use any value except 0
    double last_b_1 = 0;
    double last_b_2 = 0;
    while (last_b_1 != b && last_b_2 != b) {
        last_b_1 = b;
        b = (b + x / b / b) / 2;
        last_b_2 = b;
        b = (b + x / b / b) / 2;
    }
    return b;
}

double sqrt(double a)
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

//CHRONO FUNCTIONS
uint8 in_byte (uint16 _port)
{
	uint8 rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void out_byte (uint16 _port, uint8 _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

int get_update_in_progress_flag() {
      out_byte(cmos_address, 0x0A);
      return (in_byte(cmos_data) & 0x80);
}

unsigned char get_RTC_register(int reg) {
      out_byte(cmos_address, reg);
      return in_byte(cmos_data);
}

void read_rtc() {
      unsigned char century;
      unsigned char last_second;
      unsigned char last_minute;
      unsigned char last_hour;
      unsigned char last_day;
      unsigned char last_month;
      unsigned char last_year;
      unsigned char last_century;
      unsigned char registerB;

      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates

      while (get_update_in_progress_flag());                // Make sure an update isn't in progress
      second = get_RTC_register(0x00);
      minute = get_RTC_register(0x02);
      hour = get_RTC_register(0x04);
      day = get_RTC_register(0x07);
      month = get_RTC_register(0x08);
      year = get_RTC_register(0x09);
      if(century_register != 0) {
            century = get_RTC_register(century_register);
      }

      do {
            last_second = second;
            last_minute = minute;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;

            while (get_update_in_progress_flag());           // Make sure an update isn't in progress
            second = get_RTC_register(0x00);
            minute = get_RTC_register(0x02);
            hour = get_RTC_register(0x04);
            day = get_RTC_register(0x07);
            month = get_RTC_register(0x08);
            year = get_RTC_register(0x09);
            if(century_register != 0) {
                  century = get_RTC_register(century_register);
            }
      } while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
               (last_day != day) || (last_month != month) || (last_year != year) ||
               (last_century != century) );

      registerB = get_RTC_register(0x0B);

      // Convert BCD to binary values if necessary

      if (!(registerB & 0x04)) {
            second = (second & 0x0F) + ((second / 16) * 10);
            minute = (minute & 0x0F) + ((minute / 16) * 10);
            hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
            day = (day & 0x0F) + ((day / 16) * 10);
            month = (month & 0x0F) + ((month / 16) * 10);
            year = (year & 0x0F) + ((year / 16) * 10);
            if(century_register != 0) {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }

      // Convert 12 hour clock to 24 hour clock if necessary

      if (!(registerB & 0x02) && (hour & 0x80)) {
            hour = ((hour & 0x7F) + 12) % 24;
      }

      // Calculate the full (4-digit) year

      if(century_register != 0) {
            year += century * 100;
      } else {
            year += (CURRENT_YEAR / 100) * 100;
            if(year < CURRENT_YEAR) year += 100;
      }
}

int getTime(string args){
  read_rtc();
  if(strEql(args,"year"))
  {
     return year;
  }else if(strEql(args,"month"))
  {
     return (int)month;
  }else if(strEql(args,"day"))
  {
     return (int)day;
  }else if(strEql(args,"hour"))
  {
     return (int)hour;
  }else if(strEql(args,"minute"))
  {
     return (int)minute;
  }else if(strEql(args,"second"))
  {
     return (int)second;
  }else{
  	return -1;
  }
}
//END CHRONO FUNCTIONS
