#assembly compiler
AA:=nasm
#C compiler
CC:=gcc
#C coompiler flags
CFLAGS:=-m32 -ffreestanding -Wall 
#object file directory
ODIR:=obj
#source directory
DIR:=kernel
#OS image output directory
IMGDIR:=image

#compile the project
all:
	@mkdir -p $(ODIR)
	@$(AA) -f elf32 $(DIR)/kernel.asm -o $(ODIR)/kernel.asm.o
	@$(CC) -c $(DIR)/kernel.c -o $(ODIR)/kernel.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/assemblyFunctions.c -o $(ODIR)/assemblyFunctions.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/stringUtils.c -o $(ODIR)/stringUtils.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/byteUtils.c -o $(ODIR)/byteUtils.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/descriptorTables.c -o $(ODIR)/descriptorTables.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/isr.c -o $(ODIR)/isr.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/timer.c -o $(ODIR)/timer.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/kheap.c -o $(ODIR)/kheap.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/paging.c -o $(ODIR)/paging.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/error.c -o $(ODIR)/error.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/screenUtils.c -o $(ODIR)/screenUtils.o $(CFLAGS)
	@$(CC) -c $(DIR)/inc/kbDetect.c -o $(ODIR)/kbDetect.o $(CFLAGS)
	@$(AA) -f elf32 $(DIR)/inc/gdt.asm -o $(ODIR)/gdt.asm.o
	@$(AA) -f elf32 $(DIR)/inc/interrupt.asm -o $(ODIR)/interrupt.asm.o
	@mkdir -p $(IMGDIR)/boot

	@ld -m elf_i386 -T $(DIR)/link.ld -o $(IMGDIR)/boot/kernel.bin $(ODIR)/gdt.asm.o $(ODIR)/interrupt.asm.o $(ODIR)/error.o $(ODIR)/paging.o $(ODIR)/kheap.o $(ODIR)/byteUtils.o $(ODIR)/descriptorTables.o $(ODIR)/isr.o $(ODIR)/timer.o $(ODIR)/kernel.asm.o $(ODIR)/kernel.o $(ODIR)/assemblyFunctions.o $(ODIR)/stringUtils.o $(ODIR)/screenUtils.o $(ODIR)/kbDetect.o

#create iso file
iso:
	@mkdir -p $(IMGDIR)/boot/grub
#create crub.cfg file
	@echo -e "set timeout=15\nset default=0\n\nmenuentry "Q-OS" {\n   multiboot /boot/kernel.bin\n   boot\n}\n" > $(IMGDIR)/boot/grub/grub.cfg
	@grub-mkrescue -o q-os.iso $(IMGDIR)/
