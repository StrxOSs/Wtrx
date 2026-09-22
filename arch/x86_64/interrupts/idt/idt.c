#include "idt.h"

struct idt_entry idt[256];
struct idt_ptr    ip;

void idtsetgate(int num, uint64_t handler, uint16_t selector, uint8_t type_attr) {
	idt[num] = (struct idt_entry) {
		.offset_low 	= handler & 0xFFFF,
		.offset_mid 	= (handler >> 16) & 0xFFFF,
		.offset_high 	= (uint32_t)(handler >> 32),
		.selector 	= selector,
		.ist 		= 0,
		.type_attr 	= type_attr,
		.zero 		= 0
	};
}

void idtinstall(void) {
	ip.limit = (sizeof(struct idt_entry) * 256) -1;
	ip.base  = (uint64_t)&idt;

	idt_flush((uint64_t)&ip);
}
