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
nasm -f elf32 inc/gdt.asm -o o/gdt.asm.o
nasm -f elf32 inc/interrupt.asm -o o/interrupt.asm.o
ld -m elf_i386 -T link.ld -o q/boot/kernel.bin kernel.asm.o kernel.c.o o/assemblyFunctions.o o/stringUtils.o o/byteUtils.o o/screenUtils.o o/kbDetect.o o/descriptorTables.o o/gdt.asm.o o/interrupt.asm.o o/isr.o
grub-mkrescue -o q.iso q/
qemu-system-i386 -kernel q/boot/kernel.bin			#qemu dosen't seem to work with Update 3.1+ versions of Q OS

read a
