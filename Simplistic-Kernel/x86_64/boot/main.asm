global start
extern long_mode_start ; 64 main entry after long mode transition

extern check_cpuid
extern check_multiboot
extern check_long_mode

extern setup_page_tables
extern enable_paging

global page_table_l4
global page_table_l3
global page_table_l2

section .text
bits 32
start:
    mov esp, stack_top
    ; setup stack

    ; check if multiboot loaded succesfully
    call check_multiboot

    ; check if cpuid and extended proc info are avaible
    call check_cpuid

    ; finally check for long mode
    call check_long_mode

    ; setup paging
    call setup_page_tables
    call enable_paging

    ;load Global Descriptor Table
    lgdt [gdt64.pointer]

    ; load and jmp to 64 bit assembly
    jmp gdt64.code_segment:long_mode_start

section .bss

align 4096
page_table_l4:
    resb 4096
page_table_l3:
    resb 4096
page_table_l2:
    resb 4096
; no page_table_l1 cuz we use the huge page on page_table_l2

stack_bottom:
    resb 4096 * 4
stack_top:


section .rodata

gdt64:
    dq 0 ; zero entry
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; flags
    ;  executble | desc-type |  present  | 64bit mde
.pointer:
    dw $ - gdt64 - 1
    dq gdt64