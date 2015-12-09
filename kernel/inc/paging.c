#include "paging.h"

// The kernel's page directory
page_directory_t* kernel_directory = 0;

// The current page directory;
page_directory_t* current_directory = 0;

// A bitset of frames - used or free.
uint32* frames;
uint32 nframes;

// Defined in kheap.c
extern heap_t* kheap;
extern uint32 placement_address;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
static void set_frame(uint32 frame_addr)
{
    uint32 frame = frame_addr/0x1000;
    uint32 idx = INDEX_FROM_BIT(frame);
    uint32 off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(uint32 frame_addr)
{
    uint32 frame = frame_addr/0x1000;
    uint32 idx = INDEX_FROM_BIT(frame);
    uint32 off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// Static function to find the first free frame.
static uint32 first_frame()
{
    uint32 i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                uint32 toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
    return 0;//?
}

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
    if (page->frame != 0)
    {
        return; // Frame was already allocated, return straight away.
    }
    else
    {
        uint32 idx = first_frame(); // idx is now the index of the first free frame.
        if (idx == (uint32)-1)
        {
            // PANIC is just a macro that prints a message to the screen then hits an infinite loop.
            PANIC("No free frames!");
        }
        set_frame(idx*0x1000); // this frame is now ours!
        page->present = 1; // Mark it as present.
        page->rw = (is_writeable)?1:0; // Should the page be writeable?
        page->user = (is_kernel)?0:1; // Should the page be user-mode?
        page->frame = idx;
    }
}

// Function to deallocate a frame.
void free_frame(page_t *page)
{
    uint32 frame;
    if (!(frame=page->frame))
    {
        return; // The given page didn't actually have an allocated frame!
    }
    else
    {
        clear_frame(frame); // Frame is now free again.
        page->frame = 0x8; // Page now doesn't have a frame.
    }
}

void initialize_paging()
{
    // The size of physical memory. For the moment we
    // assume it is 16MB big.
    uint32 mem_end_page = 0x1000000;

    nframes = mem_end_page / 0x1000;
    frames = (uint32*)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));

    // Let's make a page directory.
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;

    // Map some pages in the kernel heap area.
    // Here we call get_page but not alloc_frame. This causes page_table_t's
    // to be created where necessary. We can't allocate frames yet because they
    // they need to be identity mapped first below, and yet we can't increase
    // placement_address between identity mapping and enabling the heap!
    uint32 i = 0;
    for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000)
        get_page(i, 1, kernel_directory);

    // We need to identity map (phys addr = virt addr) from
    // 0x8 to the end of used memory, so we can access this
    // transparently, as if paging wasn't enabled.
    // NOTE that we use a while loop here deliberately.
    // inside the loop body we actually change placement_address
    // by calling kmalloc(). A while loop causes this to be
    // computed on-the-fly rather than once at the start.
    // Allocate a lil' bit extra so the kernel heap can be
    // initialised properly.
    i = 0;
    while (i < placement_address+0x1000)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }

    // Now allocate those pages we mapped earlier.
    for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000)
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);

    // Before we enable paging, we must register our page fault handler.
    register_interrupt_handler(14, page_fault);

    // Now, enable paging!
    switch_page_directory(kernel_directory);

    // Initialise the kernel heap.
    kheap = create_heap(KHEAP_START, KHEAP_START+KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    __asm__ __volatile__("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    uint32 cr0;
    __asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    __asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint32 address, int make, page_directory_t *dir)
{
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    uint32 table_idx = address / 1024;

    if (dir->tables[table_idx]) // If this table is already assigned
    {
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(make)
    {
        uint32 tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(dir->tables[table_idx], 0, 0x1000);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else
    {
        return 0;
    }
}


void page_fault(registers_t regs)
{
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    uint32 faulting_address;
    __asm__ __volatile__("mov %%cr2, %0" : "=r" (faulting_address));

    // The error code gives us details of what happened.
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?

    // Output an error message.
    print("Page fault! ( ", 0x88);
    if (present) {print("present ", 0x88);}
    if (rw) {print("read-only ", 0x88);}
    if (us) {print("user-mode ", 0x88);}
    if (reserved) {print("reserved ", 0x88);}
    print(") at 0x", 0x88);
    printhex(faulting_address, 0x88);
    print("\n", 0x88);
    PANIC("Page fault");
}
