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
CFLAGS:=-m32 -ffreestanding -std=c99 $(WARNINGS)
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
INITRD:=initrd.img
GENINITRD_DIR:=genInitrd
#note: this should be replaced with something better
INITRD_REMOVE:=./make_initrd ./make_initrd.c ./initrd.img ./README.md
INITRD_CONTENT:=$(filter-out $(INITRD_REMOVE),$(shell cd $(GENINITRD_DIR); find -type f))
GENINITRD_ARGS:=$(foreach file,$(INITRD_CONTENT),$(patsubst ./%,%,$(file)) $(patsubst ./%,%,$(file)))

-include $(DEPFILES)

#compile the project
.PHONY all: $(ISO)

$(ISO): $(KERNEL) $(INITRD)
	@mkdir -p $(IMGDIR)/boot/grub
	@mkdir -p $(ODIR)
	@grub-mkrescue -o $(ISO) $(IMGDIR)/

$(KERNEL): $(CSOURCES) $(ASOURCES) $(COBJECTS) $(AOBJECTS)
	@mkdir -p $(IMGDIR)/boot/
	@ld -m elf_i386 -T $(DIR)/link.ld $(AOBJECTS) $(COBJECTS) -o $(IMGDIR)/boot/$@

$(INITRD):

	@gcc $(GENINITRD_DIR)/make_initrd.c -o $(GENINITRD_DIR)/make_initrd
	@cd $(GENINITRD_DIR); ./make_initrd $(GENINITRD_ARGS)
	@cp $(GENINITRD_DIR)/initrd.img $(IMGDIR)/boot/

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

%.ao: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

qemu: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

.PHONY clean:
# -f needed to  avoid error when file doesn't exist
	@rm -rf $(ODIR)
	@rm $(AOBJECTS)
	@rm $(COBJECTS)
	@rm -f $(IMGDIR)/boot/$(KERNEL)
	@rm -f $(ISO)
