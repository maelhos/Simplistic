global setup_page_tables
global enable_paging

extern page_table_l4
extern page_table_l3
extern page_table_l2

section .text:
bits 32
setup_page_tables:
    mov eax, page_table_l3
    or eax, 0b11 ; present, writable
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b11 ; present, writable
    mov [page_table_l3], eax

    mov ecx, 0 ; counter

.loop:

    mov eax, 0x200000 ; 2 Mb
    mul ecx
    or eax, 0b10000011 ; present, writable, huge page
    mov [page_table_l2 + ecx * 8], eax

    inc ecx
    cmp ecx, 512 ; check if whole table is mapped
    jne .loop ; if not, continue

    ret

enable_paging:
    ; pass page table location to cpu
    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE physical addressing extention (for 64bit paging)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xc0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret