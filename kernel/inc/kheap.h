#ifndef KHEAP_H
#define KHEAP_H

#include "error.h"
#include "paging.h"
#include "intTypeDefs.h"
#include "orderedArray.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE     0x20000
#define HEAP_MAGIC          0x123890AB
#define HEAP_MIN_SIZE       0x70000

/**
   Size information for a hole/block
**/
typedef struct
{
    uint32 magic;   // Magic number, used for error checking and identification.
    uint8 is_hole;   // 1 if this is a hole. 0 if this is a block.
    uint32 size;    // size of the block, including the end footer.
} header_t;

typedef struct
{
    uint32 magic;     // Magic number, same as in header_t.
    header_t *header; // Pointer to the block header.
} footer_t;

typedef struct
{
    ordered_array_t index;
    uint32 start_address; // The start of our allocated space.
    uint32 end_address;   // The end of our allocated space. May be expanded up to max_address.
    uint32 max_address;   // The maximum address the heap can be expanded to.
    uint8 supervisor;     // Should extra pages requested by us be mapped as supervisor-only?
    uint8 readonly;       // Should extra pages requested by us be mapped as read-only?
} heap_t;

/**
   Create a new heap.
**/
heap_t *create_heap(uint32 start, uint32 end, uint32 max, uint8 supervisor, uint8 readonly);

/**
   Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting
   on a page boundary.
**/
void *alloc(uint32 size, uint8 page_align, heap_t *heap);

/**
   Releases a block allocated with 'alloc'.
**/
void free(void *p, heap_t *heap);

/**
   Allocate a chunk of memory, sz in size. If align == 1,
   the chunk must be page-aligned. If phys != 0, the physical
   location of the allocated chunk will be stored into phys.

   This is the internal version of kmalloc. More user-friendly
   parameter representations are available in kmalloc, kmalloc_a,
   kmalloc_ap, kmalloc_p.
**/
uint32 kmalloc_int(uint32 sz, int align, uint32 *phys);

/**
   Allocate a chunk of memory, sz in size. The chunk must be
   page aligned.
**/
uint32 kmalloc_a(uint32 sz);

/**
   Allocate a chunk of memory, sz in size. The physical address
   is returned in phys. Phys MUST be a valid pointer to uint32!
**/
uint32 kmalloc_p(uint32 sz, uint32 *phys);

/**
   Allocate a chunk of memory, sz in size. The physical address 
   is returned in phys. It must be page-aligned.
**/
uint32 kmalloc_ap(uint32 sz, uint32 *phys);

/**
   General allocation function.
**/
uint32 kmalloc(uint32 sz);

/**
   General deallocation function.
**/
void kfree(void *p);

#endif // KHEAP_H

