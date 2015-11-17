// multiboot.h -- Declares the multiboot info structure.
//                Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "inc/intTypeDefs.h"

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400

struct multiboot
{
    uint32 flags;
    uint32 mem_lower;
    uint32 mem_upper;
    uint32 boot_device;
    uint32 cmdline;
    uint32 mods_count;
    uint32 mods_addr;
    uint32 num;
    uint32 size;
    uint32 addr;
    uint32 shndx;
    uint32 mmap_length;
    uint32 mmap_addr;
    uint32 drives_length;
    uint32 drives_addr;
    uint32 config_table;
    uint32 boot_loader_name;
    uint32 apm_table;
    uint32 vbe_control_info;
    uint32 vbe_mode_info;
    uint32 vbe_mode;
    uint32 vbe_interface_seg;
    uint32 vbe_interface_off;
    uint32 vbe_interface_len;
}  __attribute__((packed));

typedef struct multiboot_header multiboot_header_t;

#endif
