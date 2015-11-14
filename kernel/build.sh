nasm -f elf32 kernel.asm -o kernel.asm.o
gcc -m32 -c kernel.c -o kernel.c.o -ffreestanding                                                                     
gcc -m32 -c inc/assemblyFunctions.c -o o/assemblyFunctions.o -ffreestanding                                                     
gcc -m32 -c inc/stringUtils.c -o o/stringUtils.o -ffreestanding                                                     
gcc -m32 -c inc/screenUtils.c -o o/screenUtils.o -ffreestanding                                                     
gcc -m32 -c inc/kbDetect.c -o o/kbDetect.o -ffreestanding                                                             
ld -m elf_i386 -T linkAssist.ld -o q/boot/kernel.bin kernel.asm.o kernel.c.o o/assemblyFunctions.o o/stringUtils.o o/screenUtils.o o/kbDetect.o  
grub-mkrescue -o q.iso q/
virtualbox
#qemu-system-i386 -kernel q/boot/kernel.bin			#qemu dosen't seem to work with Update 3.1+ versions of Q OS

read a
