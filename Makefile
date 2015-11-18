.DEFAULT_GOAL:=all
#assembly compiler
ASM:=nasm
#ASM flags
ASMFLAGS:=-f elf32

#C compiler
CC:=gcc
#C coompiler flags
WARNINGS:=-Wall -Wextra #-pedantic -Wshadow -Wpointer-arith -Wcast-align \
            #-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            #-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            #-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS:=-m32 -ffreestanding $(WARNINGS)
#object file directory

ODIR:=kernel/o
#source directory
DIR:=kernel
#OS image output directory
IMGDIR:=kernel/q

#source and header files
CSOURCES:=$(shell find $(DIR) -type f -name "*.c")
HSOURCES:=$(shell find $(DIR) -type f -name "*.h")
ASOURCES:=$(shell find $(DIR) -type f -name "*.asm")

#object files
COBJECTS:=$(patsubst %.c,%.o,$(CSOURCES))
AOBJECTS:=$(patsubst %.asm,%.ao,$(ASOURCES))

ALLFILES:=$(SRCFILES) $(HDRFILES)

DEPFILES:=$(patsubst %.c,%.d,$(CSOURCES))

ISO:=Q-OS.iso
KERNEL:=kernel.bin

-include $(DEPFILES)

#compile the project
.PHONY all: $(ISO)

$(ISO): $(KERNEL)
	@mkdir -p $(IMGDIR)/boot/grub
	@mkdir -p $(ODIR)
	@grub-mkrescue -o $(ISO) $(IMGDIR)/

$(KERNEL): $(CSOURCES) $(ASOURCES) $(COBJECTS) $(AOBJECTS)
	@mkdir -p $(IMGDIR)/boot/
	@ld -m elf_i386 -T $(DIR)/link.ld $(AOBJECTS) $(COBJECTS) -o $(IMGDIR)/boot/$@

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.ao: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

qemu: $(ISO)
	qemu-system-i386 $(ISO)

.PHONY clean:
# -f needed to  avoid error when file doesn't exist
	@rm -rf $(ODIR)
	@rm -f $(IMGDIR)/boot/$(KERNEL)
	@rm -f $(ISO)
