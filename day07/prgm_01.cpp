//bootloader.asm
[ORG 0x7C00]
MOV AH, 0x0E
MOV AL, 'H'
INT 0x10
MOV AL, 'i'
INT 0x10
JMP $

TIMES 510 - ($ - $$) DB 0
DW 0xAA55

/c/msys64/mingw64/bin/qemu-system-x86_64 -drive format=raw,file=bootloader.bin

  //kernel.cpp
  extern "C" void kernel_main() {
    const char* message = "Hello from kernel!";
    char* video_memory = (char*)0xb8000;

    for (int i = 0; message[i] != '\0'; ++i) {
        video_memory[i * 2] = message[i];      // Character
        video_memory[i * 2 + 1] = 0x07;        // Attribute byte: light grey on black
    }




  git clone https://github.com/nativeos/pkgbuild-i386-elf-toolchain.git
cd pkgbuild-i386-elf-toolchain/i386-elf-binutils
makepkg




    

    while (1); // Infinite loop to keep kernel running
}


//kernel.h
#ifndef KERNEL_H
#define KERNEL_H

extern "C" void kernel_main();

#endif

//bootloader.asm
[ORG 0x7C00]         ; BIOS loads bootloader here

; Print "Hi"
MOV AH, 0x0E
MOV AL, 'H'
INT 0x10
MOV AL, 'i'
INT 0x10

; Load kernel from disk (sector 2) into memory at 0x1000
MOV AX, 0x1000       ; Segment where kernel will be loaded
MOV ES, AX
MOV BX, 0x0000       ; Offset within segment
MOV AH, 0x02         ; BIOS read sector function
MOV AL, 1            ; Number of sectors to read
MOV CH, 0            ; Cylinder
MOV CL, 2            ; Sector (starts at 1)
MOV DH, 0            ; Head
INT 0x13             ; BIOS disk read

; Jump to kernel
JMP 0x1000

; Boot signature
TIMES 510 - ($ - $$) DB 0
DW 0xAA55


  //linker.ld
  ENTRY(kernel_main)

SECTIONS {
    . = 0x1000;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}



git clone https://github.com/nativeos/pkgbuild-i386-elf-toolchain.git
cd pkgbuild-i386-elf-toolchain/i386-elf-binutils
makepkg



git clone https://github.com/nativeos/pkgbuild-i386-elf-toolchain.git

make[1]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build'
make[1]: Nothing to be done for 'all-target'.
make[2]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/intl'
make[2]: Nothing to be done for 'all'.
make[2]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/intl'
make[2]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/libiberty'
make[2]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/zlib'
true "AR_FLAGS=rc" "CC_FOR_BUILD=gcc" "CFLAGS=-march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS" "CXXFLAGS=-march=nocona -msahf -mtune=generic -O2 -pipe" "CFLAGS_FOR_BUILD=-march=nocona -msahf -mtune=generic -O2 -pipe" "CFLAGS_FOR_TARGET=-g -O2" "INSTALL=/usr/bin/install -c" "INSTALL_DATA=/usr/bin/install -c -m 644" "INSTALL_PROGRAM=/usr/bin/install -c" "INSTALL_SCRIPT=/usr/bin/install -c" "LDFLAGS=-static-libstdc++ -static-libgcc -Wl,--stack,12582912" "LIBCFLAGS=-march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS" "LIBCFLAGS_FOR_TARGET=-g -O2" "MAKE=make" "MAKEINFO=makeinfo --split-size=5000000 --split-size=5000000 " "PICFLAG=" "PICFLAG_FOR_TARGET=" "SHELL=/bin/sh" "EXPECT=expect" "RUNTEST=runtest" "RUNTESTFLAGS=" "exec_prefix=/usr" "infodir=/usr/share/info" "libdir=/usr/lib" "prefix=/usr" "tooldir=/usr/i386-elf" "AR=ar" "AS=as" "CC=gcc" "CXX=g++" "LD=C:/msys64/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/15.1.0/../../../../x86_64-w64-mingw32/bin/ld.exe" "LIBCFLAGS=-march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS" "NM=nm" "PICFLAG=" "RANLIB=ranlib" "DESTDIR=" DO=all multi-do # make
make[2]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/zlib'
make[2]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/etc'
make[2]: Nothing to be done for 'all'.
make[2]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/etc'
if [ x"" != x ]; then \
  gcc -c -DHAVE_CONFIG_H -march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS  -I. -I../../binutils-2.28/libiberty/../include  -W -Wall -Wwrite-strings -Wc++-compat -Wstrict-prototypes -Wshadow=local -pedantic  -D_GNU_SOURCE  ../../binutils-2.28/libiberty/waitpid.c -o pic/waitpid.o; \
else true; fi
if [ x"" != x ]; then \
  gcc -c -DHAVE_CONFIG_H -march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS  -I. -I../../binutils-2.28/libiberty/../include  -W -Wall -Wwrite-strings -Wc++-compat -Wstrict-prototypes -Wshadow=local -pedantic  -D_GNU_SOURCE   ../../binutils-2.28/libiberty/waitpid.c -o noasan/waitpid.o; \
else true; fi
gcc -c -DHAVE_CONFIG_H -march=nocona -msahf -mtune=generic -O2 -pipe -D__USE_MINGW_ACCESS  -I. -I../../binutils-2.28/libiberty/../include  -W -Wall -Wwrite-strings -Wc++-compat -Wstrict-prototypes -Wshadow=local -pedantic  -D_GNU_SOURCE ../../binutils-2.28/libiberty/waitpid.c -o waitpid.o
make[3]: Entering directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/libiberty/testsuite'
make[3]: Nothing to be done for 'all'.
make[3]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/libiberty/testsuite'
../../binutils-2.28/libiberty/waitpid.c: In function 'waitpid':
../../binutils-2.28/libiberty/waitpid.c:31:18: error: implicit declaration of function 'wait'; did you mean 'waitpid'? [-Wimplicit-function-declaration]
   31 |       int wpid = wait(stat_loc);
      |                  ^~~~
      |                  waitpid
make[2]: *** [Makefile:1629: waitpid.o] Error 1
make[2]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build/libiberty'
make[1]: *** [Makefile:8056: all-libiberty] Error 2
make[1]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build'
