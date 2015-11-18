# Compiling Q OS on your own computer

When compiling the Q OS files, it is important to have the correct compilers downloaded on your computer. You can get everything you need to compile Q OS Pre Alpha on apt-get systems using this command:

    sudo apt-get nasm gcc g++ grub xorriso qemu-system-x86 git
    
Once you have ran that command and therefore donwnloaded all the required software to compile Q OS, you will need to download the source code from the Q OS GitHub page using this command:

    git clone https://github.com/raphydaphy/Q-OS.git
   
Now you are ready to compile Q OS. Go into the folder where you downloaded the Q OS source code files and run this command to compile the code:

    sudo ./build.sh
    
If you have done everything correctly, a NASM window should open which will let you test your compiled version of Q OS in the NASM virtualiser. You will notice that a lot of .o files will generate in <code>/kernel/o</code>. These files are unlinked compiled versions of each .c file in the Q OS file tree. In <code>/kernel/q</code> there should be a file generated called <code>kernel.bin</code> which is a binary file that stores everything that NASM needs to virtualise Q OS. The file <code>q.iso</code> should also generate, in the <code>/kernel/<code> directory. This is a bootable ISO image that you can run in virtualbox or use with <code>sudo dd</code> to create a bootable Q OS USB.
