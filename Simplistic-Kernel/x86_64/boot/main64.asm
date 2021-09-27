global long_mode_start

extern _start

section .text
bits 64

long_mode_start:
    ; load null values for the cpu to work
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; yeahhh were jumping to C now... no more asm
    call _start
    hlt
