#include "mouse.h"

uint8 mouse_cycle=0;     //unsigned char
int8 mouse_byte[3];    //signed char
int8 mouse_x=0;         //signed char
int8 mouse_y=0;         //signed char

//Mouse functions
void mouse_handler(registers_t regs) //struct regs *a_r (not used but just there)
{
  static uint8 cycle = 0;
  static int8 mouse_bytes[3];
  mouse_bytes[cycle++] = inportb(0x60);
 
  if (cycle == 3) { // if we have all the 3 bytes...
    cycle = 0; // reset the counter
    

    if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
 print("\nButton is pressed",2);
      return; // the mouse only sends information about overflowing, do not care about it and return
    if (!(mouse_bytes[0] & 0x20))
 print("\nButton is pressed",2);
    //  y |= 0xFFFFFF00; delta-y is a negative value
    if (!(mouse_bytes[0] & 0x10))
 print("\nButton is pressed",2);
   //   x |= 0xFFFFFF00; //delta-x is a negative value
    if (mouse_bytes[0] & 0x4)

      print("\nMiddle button is pressed",2);
    if (mouse_bytes[0] & 0x2)
      print("\nRight button is pressed!n",2);
    if (mouse_bytes[0] & 0x1)
      print("\nLeft button is pressed!n",2);
    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  }
}

void mouse_wait(uint8 a_type) //unsigned char
{
  uint32 _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inportb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

void mouse_write(uint8 a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outportb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outportb(0x60, a_write);
}

uint8 mouse_read()
{
  //Get's response from mouse
  mouse_wait(0); 
  return inportb(0x60);
}

void mouse_install()
{
  uint8 _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  outportb(0x64, 0xA8);
  
  //Enable the interrupts
  mouse_wait(1);
  outportb(0x64, 0x20);
  mouse_wait(0);
  _status=(inportb(0x60) | 2);
  mouse_wait(1);
  outportb(0x64, 0x60);
  mouse_wait(1);
  outportb(0x60, _status);
  
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
  
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read(); 

 //Acknowledge

  //Setup the mouse handler
  register_interrupt_handler(IRQ12, mouse_handler);
}
