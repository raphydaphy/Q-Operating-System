#include "isr.h"

void isr_handler(registers_t regs)
{
   print("recieved interrupt: ", 0x08);
   printint(regs.int_no, 0x08);
   printch('\n', 0x08);
}
