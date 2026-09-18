#ifndef WTRX_PIC_H
#define WTRX_PIC_H

#include <stdint.h>

#define MASTERPIC	0x20 // Master PIC
#define SLAVEPIC	0xA0 // slave pic
#define MASTER_COMMAND	MASTERPIC
#define MASTER_DATA	(MASTERPIC + 1)
#define SLAVE_COMMAND	SLAVEPIC
#define SLAVE_DATA	(SLAVEPIC + 1)

// eoi_int part
#define PIC_EOI 	0x20

// PART ICW
#define ICW1_ICW4	0x1
#define ICW1_SINGLE	0x2
#define ICW1_INTERVAL4	0x4
#define ICW_LEVEL	0x08
#define ICW1_INIT	0x10

#define ICW4_8086	0x01
#define ICW4_AUTO	0x02
#define ICW_BUF_SLAVE	0x08
#define ICW_BUF_MASTER	0x0C
#define ICW4_SFNM	0x10

// cascade irq
#define CASCADE_IRQ	2

// functions.
void pic2eoi(uint8_t irq);
void picremap(int master_offset, int slave_offset);
void picdissable(void);


#endif /* WTRX_PIC_H */
