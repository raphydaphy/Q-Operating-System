To compile Q-OS you need to compile a cross compiler.

Needed packages
---------------

    gcc 5.x
    g++ 5.x
    GNU Make
    GNU Bison
    Flex
    Texinfo
    ISL (optional)
    CLooG (optional)

    tar
    lzip

For Mac users:
If you use OS X 10.7 or older you need to install gcc and do this:

    # This is only necessary for OS X users running 10.7 or below.
    export CC=/usr/bin/gcc-5.X
    export CXX=/usr/bin/g++-5.X
    export CPP=/usr/bin/cpp-5.X
    export LD=/usr/bin/gcc-5.X

note: don't make these permanent

Installing
----------
Run build_cross_compiler.sh script.
After it's finished run:

    . ./set_path.sh

Note: you need to do that every time you start new console session. Or permanently change your $PATH.

Compiling Q-OS
--------------
To compile:

    make

To compile and run:

    make qemu
