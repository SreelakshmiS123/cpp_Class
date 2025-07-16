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







   tail -n 100 build-log.txt
checking size of void *... (cached) 8
checking size of long... (cached) 4
checking for alloca.h... (cached) no
checking for stddef.h... (cached) yes
checking for string.h... (cached) yes
checking for strings.h... (cached) yes
checking for stdlib.h... (cached) yes
checking for time.h... (cached) yes
checking for unistd.h... (cached) yes
config.status: creating Makefile
checking for wchar.h... (cached) yes
checking for wctype.h... (cached) yes
config.status: creating po/Makefile.in
checking for fcntl.h... (cached) yes
config.status: creating config.h
checking for sys/file.h... (cached) yes
config.status: config.h is unchanged
config.status: executing depfiles commands
checking for sys/time.h... (cached) yes
checking for sys/stat.h... (cached) yes
checking for sys/resource.h... (cached) no
looking for a compliant stdint.h in stdint.h, checking for uintmax_t... config.status: executing libtool commands
yes
checking for uintptr_t... config.status: executing default-1 commands
config.status: creating po/POTFILES
config.status: creating po/Makefile
yes
checking for int_least32_t... yes
checking for int_fast32_t... yes
checking for uint64_t... yes
checking what to include in bfd_stdint.h... stdint.h (already complete)
checking whether time.h and sys/time.h may both be included... (cached) yes
checking for dirent.h that defines DIR... (cached) yes
checking for library containing opendir... (cached) none required
checking whether string.h and strings.h may both be included... (cached) yes
checking for fcntl... (cached) no
checking for getpagesize... (cached) yes
checking for setitimer... (cached) no
checking for sysconf... (cached) no
config.status: creating Makefile
checking for fdopen... (cached) yes
checking for getuid... (cached) no
checking for getgid... (cached) no
config.status: creating po/Makefile.in
checking for fileno... (cached) yes
checking for strtoull... (cached) yes
config.status: creating config.h
checking for getrlimit... (cached) no
config.status: config.h is unchanged
checking whether basename is declared... (cached) no
config.status: executing depfiles commands
checking whether ftello is declared... (cached) yes
checking whether ftello64 is declared... (cached) yes
checking whether fseeko is declared... (cached) yes
checking whether fseeko64 is declared... (cached) yes
config.status: executing libtool commands
checking whether ffs is declared... (cached) no
checking whether free is declared... (cached) yes
checking whether getenv is declared... (cached) yes
config.status: executing default-1 commands
checking whether malloc is declared... (cached) yes
config.status: creating po/POTFILES
checking whether realloc is declared... (cached) yes
config.status: creating po/Makefile
checking whether stpcpy is declared... (cached) no
checking whether strstr is declared... (cached) yes
checking whether asprintf is declared... (cached) yes
checking whether vasprintf is declared... (cached) yes
checking whether snprintf is declared... (cached) yes
checking whether vsnprintf is declared... (cached) yes
checking whether strnlen is declared... (cached) yes
checking linker --as-needed support... (cached) yes
checking for cos in -lm... (cached) yes
checking for gcc version with buggy 64-bit support... no
checking for ftello... (cached) yes
checking for ftello64... (cached) yes
checking for fseeko... (cached) yes
checking for fseeko64... (cached) yes
checking for fopen64... (cached) yes
checking size of off_t... (cached) 8
checking file_ptr type... BFD_HOST_64_BIT
checking for stdlib.h... (cached) yes
checking for unistd.h... (cached) yes
checking for getpagesize... (cached) yes
checking for working mmap... (cached) no
checking for madvise... (cached) no
checking for mprotect... (cached) yes
configure: creating ./config.status
config.status: creating Makefile
config.status: creating doc/Makefile
config.status: creating bfd-in3.h
config.status: creating po/Makefile.in
config.status: creating config.h
config.status: config.h is unchanged
config.status: executing depfiles commands
config.status: executing libtool commands
config.status: executing default-1 commands
config.status: executing bfd_stdint.h commands
config.status: executing default commands
make[1]: Leaving directory '/c/MyOSproject/src/pkgbuild-i386-elf-toolchain/i386-elf-binutils/src/binutils-build'

