#Q OS Simple Build Script
#I will be moving this to makefile when we have more files in the project [eta: 1 week]

#compile the assembly and c code into .bin files
nasm -f elf32 kernel.asm -o kasm.bin
gcc -m32 -c kernel.c -o kc.o -ffreestanding

#link the files using the link.ld file into the kernel.bin combined file
ld -m elf_i386 -T link.ld -o q/boot/kernel.bin kasm.o kc.o

#open the kernel in qemu to test it
qemu-system-i386 -kernel q/boot/kernel.bin

#when the qemu session is closed, build the iso image of the kernel - Currently disabled to save time when compiling
grub-mkrescue -o q.iso q/

read a
