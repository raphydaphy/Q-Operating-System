#include "isr.h"
#include "screenUtils.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8 n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    else
    {
        print("unhandled interrupt: ", 0x0F);
        printint(regs.int_no, 0x0F);
        printch('\n', 0x0F);
    }
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outportb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outportb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}
