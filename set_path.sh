#!/bin/bash
contains() {
    string="$1"
    substring="$2"
    if test "${string#*$substring}" != "$string"
    then
        return 0    # $substring is in $string
    else
        return 1    # $substring is not in $string
    fi
}

cd cross
export PREFIX="$(pwd)"
export TARGET="i686-elf"
export ADD_PATH="$PREFIX/bin"
if ! contains $PATH  $ADD_PATH
then
    export PATH="$ADD_PATH:$PATH"
    echo "PATH set to $PATH"
else
    echo "Path already set"
fi
cd ..
