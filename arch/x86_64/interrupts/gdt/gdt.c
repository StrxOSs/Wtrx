#include "gdt.h"

struct gdt_entry gdt[5];
struct gdt_ptr    gp;

extern void gdt_flush(uint64_t gdt_ptr_addr);

void gdt_set_gate(int num, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = 0;
    gdt[num].base_middle = 0;
    gdt[num].base_high   = 0;
    gdt[num].limit_low   = 0;
    gdt[num].granularity = gran;
    gdt[num].access      = access;
}

void gdt_install(void) {
    gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gp.base  = (uint64_t)&gdt;

    gdt_set_gate(0, 0x00, 0x00);
    gdt_set_gate(1, 0x9A, 0x20);
    gdt_set_gate(2, 0x92, 0x00);
    gdt_set_gate(3, 0xFA, 0x20);
    gdt_set_gate(4, 0xF2, 0x00);

    gdt_flush((uint64_t)&gp);
}
