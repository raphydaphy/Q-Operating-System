cd ..
make
make iso
qemu-system-i386 -kernel kernel/q/boot/kernel.bin

read a
