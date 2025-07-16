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




 grep -i error build-log.txt
checking for library containing strerror... (cached) none required
checking for strerror... (cached) yes
checking for library containing strerror... (cached) none required
checking for library containing strerror... (cached) none required
checking for library containing strerror... (cached) none required
checking for library containing strerror... (cached) none required
checking for style of include used by make... checking for style of include used by make... checking for strerror... (cached) yes
checking for library containing strerror... (cached) none required
checking for library containing strerror... (cached) none required
checking for library containing strerror... (cached) none required
echo ./regex.o ./cplus-dem.o ./cp-demangle.o ./md5.o ./sha1.o ./alloca.o ./argv.o ./choose-temp.o ./concat.o ./cp-demint.o ./crc32.o ./d-demangle.o ./dwarfnames.o ./dyn-string.o ./fdmatch.o ./fibheap.o ./filename_cmp.o ./floatformat.o ./fnmatch.o ./fopen_unlocked.o ./getopt.o ./getopt1.o ./getpwd.o ./getruntime.o ./hashtab.o ./hex.o ./lbasename.o ./lrealpath.o ./make-relative-prefix.o ./make-temp-file.o ./objalloc.o ./obstack.o ./partition.o ./pexecute.o ./physmem.o ./pex-common.o ./pex-one.o ./pex-win32.o ./vprintf-support.o ./rust-demangle.o ./safe-ctype.o ./simple-object.o ./simple-object-coff.o ./simple-object-elf.o ./simple-object-mach-o.o ./simple-object-xcoff.o ./sort.o ./spaces.o ./splay-tree.o ./stack-limit.o ./strerror.o ./strsignal.o ./timeval-utils.o ./unlink-if-ordinary.o ./xasprintf.o ./xatexit.o ./xexit.o ./xmalloc.o ./xmemdup.o ./xstrdup.o ./xstrerror.o ./xstrndup.o ./xvasprintf.o > required-list

config.status: executing default commands
make[1]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build'

