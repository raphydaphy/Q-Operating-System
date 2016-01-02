; Q OS Kernel programmed by Raph Hennessy
; To be moved to 64 Bit Long-Mode [ETA: 2 weeks]
; This file's main purpose is to declare some important variables for the OS and load the kernel.c file
; This is compiled into kasm.o which is linked with kc.o to create the kernel.bin file

bits    32                      ; this is a 32 bit operating system, we are declaring that here
section     .text               ; establish the start of the text section
	align   4                   ; we need 4 align things because this is a 32 bit operating system
	dd	0x1BADB002              ; "Magic Number" boot sequence
	dd	0x00                    ; a blank variable to form the boot code
	dd	- (0x1BADB002+0x00)     ; boot code

global start                    ; declare a global 'start' function
extern kmain                    ; refers to the external 'kmain' function in kernel.c
start:                          ; create the start loop so we can go to it in the code later
    push ebx

	cli                         ; clear interupts
	call kmain                  ; calls the kmain function from kernel.c
	jmp $                       ; halts cpu execution of kernel.asm
