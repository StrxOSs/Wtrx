[BITS 16]
global start

section .boot
start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov [boot_drive], dl

    mov ah, 0x02
    mov al, 69
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]
    mov bx, 0x1000
    mov es, bx
    xor bx, bx
    int 0x13
    jc disk_error

    in al, 0x92
    or al, 2
    out 0x92, al

    lgdt [gdt32.pointer]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp gdt32.code:0x10000

disk_error:
    mov si, disk_error_msg
.print:
    lodsb
    or al, al
    jz .hang
    mov ah, 0x0E
    int 0x10
    jmp .print
.hang:
    cli
    hlt
    jmp .hang

disk_error_msg: db "DISK READ ERROR", 0
boot_drive: db 0

gdt32:
    dq 0
.code: equ $ - gdt32
    dd 0xFFFF
    db 0
    db 10011010b
    db 11001111b
    db 0
.data: equ $ - gdt32
    dd 0xFFFF
    db 0
    db 10010010b
    db 11001111b
    db 0
.pointer:
    dw $ - gdt32 - 1
    dd gdt32

times 510-($-$$) db 0
dw 0xAA55

section .text
[BITS 32]
global protected_mode_start
protected_mode_start:
    mov ax, gdt32_data_sel
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, stack_top

    mov edi, p4_table
    mov ecx, 3072
    xor eax, eax
    rep stosd

    mov eax, p3_table
    or eax, 0b11
    mov [p4_table], eax

    mov eax, p2_table
    or eax, 0b11
    mov [p3_table], eax

    mov eax, 0x000000 | 0b10000011
    mov [p2_table], eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov eax, p4_table
    mov cr3, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    lgdt [gdt64.pointer]
    jmp gdt64.code:long_mode_start

[BITS 64]
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    extern wtrx_main
    call wtrx_main

    cli
.hlt:
    hlt
    jmp .hlt

gdt32_data_sel equ 0x10

gdt64:
    dq 0
.code: equ $ - gdt64
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .bss
align 4096
p4_table: resb 4096
p3_table: resb 4096
p2_table: resb 4096
stack_bottom: resb 16384
stack_top:
