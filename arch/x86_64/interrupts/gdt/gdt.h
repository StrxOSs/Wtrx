#ifndef WTRX_GDT_H
#define WTRX_GDT_H

#include <stdint.h>

struct __attribute__((packed)) gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
};

struct __attribute__((packed)) gdt_ptr {
    uint16_t limit;
    uint64_t base;
};

void gdt_install(void);
void gdt_set_gate(int num, uint8_t access, uint8_t gran);

#endif /* WTRX_GDT_H */
