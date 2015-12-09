
#include "descriptorTables.h"
#include "isr.h"

// Lets us access our ASM functions from our C code.
extern void gdt_flush(uint32);
extern void idt_flush(uint32);

// Internal function prototypes.
static void init_gdt();
static void init_idt();
static void gdt_set_gate(int32,uint32,uint32,uint8,uint8);
static void idt_set_gate(uint8,uint32,uint16,uint8);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

// Extern the ISR handler array so we can nullify them on startup.
extern isr_t interrupt_handlers[];

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables()
{

    // Initialise the global descriptor table.
    init_gdt();
    // Initialise the interrupt descriptor table.
    init_idt();
    // Nullify all the interrupt handlers.
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

static void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (uint32)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32)&gdt_ptr);
}

// Set the value of one GDT entry.
static void gdt_set_gate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

static void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (uint32)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

    // Remap the irq table.
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);

    idt_set_gate( 0, (uint32)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint32)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint32)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uint32)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (uint32)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (uint32)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (uint32)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (uint32)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (uint32)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (uint32)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (uint32)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);
    idt_set_gate(32, (uint32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32)irq15, 0x08, 0x8E);

    idt_flush((uint32)&idt_ptr);
}

static void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags   = flags /* | 0x60 */;
}
