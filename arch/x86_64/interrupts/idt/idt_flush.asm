global idt_flush
[bits 64]

idt_flush:
    lidt [rdi]
    ret
