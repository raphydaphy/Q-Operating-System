# Compiling Q OS on your own computer

When compiling the Q OS files, it is important to have the correct compilers downloaded on your computer. You can get everything you need to compile Q OS Pre Alpha on apt-get systems using this command:

    sudo apt-get install nasm gcc g++ grub xorriso qemu-system-x86 git
    
Once you have ran that command and therefore donwnloaded all the required software to compile Q OS, you will need to download the source code from the Q OS GitHub page using this command:

    git clone https://github.com/raphydaphy/Q-OS.git
   
Now you are ready to compile Q OS. Go into the folder where you downloaded the Q OS source code files and run this command to compile the code:

    make qemu
    
If you have done everything correctly, a qemu window should open which will let you test your compiled version of Q OS in the virtualiser. You will notice that a lot of .o files will generate in `/kernel/o`. These files are unlinked compiled versions of each .c file in the Q OS file tree. In the Q OS folder, there should be a file generated called `Q-OS.iso` which is the image file that qemu needs to virtualise Q OS. The image then can be ran in virtualbox or made into a bootable usb using the command `sudo dd`.

## Troubleshooting

If there are errors when you try to compile or boot Q OS, this section might have the right solutions for you that will help you fix your problem. It is divided up into headings for each main kind of error that you might occur when building or using the files for Q OS.

### Compiler Warnings

If you are not working on the code of Q OS and just want to try using it, it can seem daunting when you are faced with multiple compiler warnings when you run the Q OS makefile in Terminal. Most of the warning messages are harmless and Q OS should still work fine, but sometimes, although it is rare, a warning message when running the makefile could result in non functional code when running Q OS. If you are unsure if the messages shown in Terminal are errors or warnings, you can look closely at the message and it will tell you. Here is an example of a warning message you might get when compiling Q OS

    kernel/inc/timer.c: In function ‘timer_callback’:
    kernel/inc/timer.c:10:40: warning: unused parameter ‘regs’ [-Wunused-parameter]
    static void timer_callback(registers_t regs)
                                           ^

You can tell this is simply a warning by the second line of the message where it says `warning: unused parameter`. This kind of warning is very common because we have configured the compiler to warn us about any small potentially unwanted code that could help reduce the filesize of the ISO, the boot time and remove bugs. You don't need to worry about warnings unless you are unable to run the OS using `make qemu`. If this is the case, please submit an Issue in the Issue Tracker for Q OS which you can access by clicking the second icon from the top in the icon bar on the side of the screen on the Q OS github page and copy the warning messages that you see in the Terminal output when compiling the Q OS code. However, please only submit an Issue Report if the warning appears to be affecting Q OS when you run it in qemu, or if you are also reciving `error` messages as well as warnings because error messages are almost always fatal and will stop the code from working.

### Grub screen when Booting Q OS

If you are trying to run Q OS in either qemu or on a real computer and when you turn it on you see a screen with text that looks something like the example below, you will probably be irritated or confused.

        GNU GRUB  version 2.02~bta2-9ubuntu1.4
    Minimal BASH-like line editing is supported. For the first word, TAB lists possible command completions. Anywhere else TAB lists possible device or file completions. ESC at any time exits.
    
    grub>
    
Luckily, in most cases it is relativly easy to get out of this screen and return to the normal Q OS screen. If you are booting Q OS using the `make qemu` command within Ubuntu or another `apt-get` based linux distribution, simply type each of these commands, one at a time, into the `grub>` or `grub-rescue>` command line interface.

    set root=(cd)
    set prefix=(cd)/boot/grub
    insmod multiboot
    insmod normal
    multiboot /boot/kernel.bin
    module /boot/initrd.img
    normal
    
You should now see a screen that has a box with different options to select, or only a single one based on your setup and version of Q OS you are using. At the bottom of the screen, you should see the text shown below.

    Use the Up and Down keys to select which entry is highlighted. 
    Press enter to boot the selected OS, 'e' to edit the commands before booting or 'c' for a command line.
    
The exact text you see might be slightly different, but if you see something similar to that, then all you need to do now is press `e` on your keyboard to bring up a screen with some code on it and at the bottom it should say the text you see just below this paragraph.

    Minimum Emacs-like screen editing is supported. TAB lists completions. Press Ctrl-x or F10 bo boot, Ctrl-c or F2 for a command-line or ESC to discard edits and return to the GRUB menu.
    
If you see that text, the last step you need to do is, using the arrow keys to move your cursor around the document, find any times that the code says `(hd0)` or `(hd96)` and change it by moving the cursor to the end of the text you want to delete and pressing backspace untill it is all gone then typing the new text, which should be `(cd)`.

Once you have made sure that you have only changed the `(hd0)` and `(hd96)` instances to `(cd)` and everything else in the small code file you can see on the screen remains intact, press the <code>F10</code> key on your keyboard, or on some system you will need to use the keyboard shortcut `FN + F10`, and you should now see the Q OS startup screen, which currently is only some text saying

    Welcome to Q OS
    
If you see this, you are now in Q OS and you can use the keyboard to enter commands. Well done, you fixed an error!

However, if you are booting Q OS on a real device, there is no exact instructions on how to get out of the <code>grub</code> interface at the moment because of the numerous combination of hardware and firmware that result in different steps to resolve the issue. When Q OS is developed further, we will probably release instructions on exactly how to install Q OS on real hardware. For now, use Q OS in a virtual machine and boot via a CD if you have an option. If you are booting from a CD, just use the steps above for booting in qemu because they are the same.

If you are still having issues, try replacing `(cd)` in the final step of fixing the issue with `(hd0)` and it might fix.
