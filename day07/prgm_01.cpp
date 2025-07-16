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

/*

@deftypefn Supplemental int waitpid (int @var{pid}, int *@var{status}, int)

This is a wrapper around the @code{wait} function.  Any ``special''
values of @var{pid} depend on your implementation of @code{wait}, as
does the return value.  The third argument is unused in @libib{}.

@end deftypefn

*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "ansidecl.h"

/* On some systems (such as WindISS), you must include <sys/types.h>
   to get the definition of "pid_t" before you include <sys/wait.h>.  */

^G Help          ^O Write Out     ^F Where Is      ^K Cut           ^T Execute       ^C Location      M-U Undo         M-A Set Mark     M-] To Bracket   M-B Previous
^X Exit          ^R Read File     ^\ Replace       ^U Paste         ^J Justify       ^/ Go To Line    M-E Redo         M-6 Copy         ^B Where Was     M-F Next
