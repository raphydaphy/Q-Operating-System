nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o -ffreestanding                                                                     
gcc -m32 -c inc/system.c -o o/system.o -ffreestanding                                                     
gcc -m32 -c inc/string.c -o o/string.o -ffreestanding                                                     
gcc -m32 -c inc/screen.c -o o/screen.o -ffreestanding                                                     
gcc -m32 -c inc/kb.c -o o/kb.o -ffreestanding                                                             
ld -m elf_i386 -T link.ld -o q/boot/kernel.bin kasm.o kc.o o/system.o o/string.o o/screen.o o/kb.o  
qemu-system-i386 -kernel q/boot/kernel.bin
#grub-mkrescue -o q.iso q/

read a
