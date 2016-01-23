#!/bin/sh
set -e

mkdir cross
cd cross

export PREFIX="$(pwd)"
export TARGET="i686-elf"
export PATH="$PREFIX/bin:$PATH"

echo $PREFIX $TARGET $PATH

BINUTILS_VER="binutils-2.25.1"
curl -o $BINUTILS_VER.tar.bz2 http://ftp.gnu.org/gnu/binutils/$BINUTILS_VER.tar.bz2
tar -xvf $BINUTILS_VER.tar.bz2
mkdir build-binutils
cd build-binutils
../$BINUTILS_VER/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j4
make install
cd ..

GMP_VER="gmp-6.1.0"
MPFR_VER="mpfr-3.1.3"
MPC_VER="mpc-1.0.3"
GCC_VER="gcc-5.3.0"
#prepare GCC for installation
curl -o $GMP_VER.tar.lz https://gmplib.org/download/gmp/$GMP_VER.tar.lz
curl -o $MPFR_VER.tar.gz http://www.mpfr.org/mpfr-current/$MPFR_VER.tar.gz
curl -o $MPC_VER.tar.gz ftp://ftp.gnu.org/gnu/mpc/$MPC_VER.tar.gz
tar --lzip -xvf $GMP_VER.tar.lz
tar -xvf $MPFR_VER.tar.gz
tar -xvf $MPC_VER.tar.gz
curl -o $GCC_VER.tar.gz ftp://ftp.gnu.org/gnu/gcc/gcc-5.3.0/$GCC_VER.tar.gz
tar -xvf $GCC_VER.tar.gz
mv $GMP_VER $GCC_VER/gmp
mv $MPFR_VER $GCC_VER/mpfr
mv $MPC_VER $GCC_VER/mpc

mkdir build-gcc
cd build-gcc
../$GCC_VER/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j4 all-gcc
make -j4 all-target-libgcc
make install-gcc
make install-target-libgcc
