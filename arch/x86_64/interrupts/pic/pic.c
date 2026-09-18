#include "pic.h"
#include <arch/x86_64/cpu/io.h>

void pic2eoi(uint8_t irq) {
	if (irq >= 8) {
		outb(SLAVE_COMMAND, PIC_EOI);
	}

	outb(MASTER_COMMAND, PIC_EOI);
}

void picremap(int master_offset, int slave_offset) {
	outb(MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
	iowait();
	outb(SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);
	iowait();
	outb(MASTER_DATA, master_offset);
	iowait();
	outb(SLAVE_DATA, slave_offset);
	iowait();
	outb(MASTER_DATA, 1 << CASCADE_IRQ);
	iowait();
	outb(SLAVE_DATA, CASCADE_IRQ);

	iowait();
	outb(MASTER_DATA, ICW4_8086);
	iowait();
	outb(SLAVE_DATA, ICW4_8086);

	iowait();
	outb(MASTER_DATA, 0);
	outb(SLAVE_DATA, 0);
}

void picdissable(void) {
	outb(MASTER_DATA, 0xff);
	outb(SLAVE_DATA, 0xff);
}
