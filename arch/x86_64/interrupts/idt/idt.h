#ifndef WTRX_IDT_H
#define WTRX_IDT_H

#include <stdint.h>

extern void idt_flush(uint64_t idt_ptr_addr);

struct __attribute__((packed)) idt_entry {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t  ist;
	uint8_t  type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
};

struct __attribute__((packed)) idt_ptr {
	uint16_t limit;
	uint64_t base;
};

void idtsetgate(int num, uint64_t handler, uint16_t selector, uint8_t type_attr);
void idtinstall(void);

#endif /* WTRX_IDT_H */
