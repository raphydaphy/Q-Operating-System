mkdir o

nasm -f elf32 kernel.asm -o kernel.asm.o
gcc -m32 -c kernel.c -o kernel.c.o -ffreestanding
gcc -m32 -c inc/assemblyFunctions.c -o o/assemblyFunctions.o -ffreestanding
gcc -m32 -c inc/stringUtils.c -o o/stringUtils.o -ffreestanding
gcc -m32 -c inc/byteUtils.c -o o/byteUtils.o -ffreestanding
gcc -m32 -c inc/screenUtils.c -o o/screenUtils.o -ffreestanding
gcc -m32 -c inc/kbDetect.c -o o/kbDetect.o -ffreestanding
gcc -m32 -c inc/descriptorTables.c -o o/descriptorTables.o -ffreestanding
gcc -m32 -c inc/isr.c -o o/isr.o -ffreestanding
gcc -m32 -c inc/timer.c -o o/timer.o -ffreestanding
gcc -m32 -c inc/kheap.c -o o/kheap.o -ffreestanding
gcc -m32 -c inc/paging.c -o o/paging.o -ffreestanding
gcc -m32 -c inc/error.c -o o/error.o -ffreestanding
gcc -m32 -c inc/fs.c -o o/fs.o -ffreestanding
gcc -m32 -c inc/initrd.c -o o/initrd.o -ffreestanding
gcc -m32 -c inc/orderedArray.c -o o/orderedArray.o -ffreestanding
nasm -f elf32 inc/gdt.asm -o o/gdt.asm.o
nasm -f elf32 inc/interrupt.asm -o o/interrupt.asm.o
ld -m elf_i386 -T link.ld -o q/boot/kernel.bin kernel.asm.o kernel.c.o o/assemblyFunctions.o o/stringUtils.o o/byteUtils.o o/screenUtils.o o/kbDetect.o o/descriptorTables.o o/gdt.asm.o o/interrupt.asm.o o/isr.o o/timer.o o/kheap.o o/paging.o o/error.o o/orderedArray.o o/fs.o o/initrd.o
grub-mkrescue -o q.iso q/
qemu-system-i386 q.iso			#qemu dosen't seem to work with Update 3.1+ versions of Q OS

read a
