global check_multiboot

extern error

section .text
bits 32
check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multoboot
    ret
.no_multoboot:
    mov al, "M"
    jmp error