/*
 *  if u read this fucking shit, please
 *  dont confuse IO LIB to I/O, this is I/O
 *  thx for read this message :)
 */

#ifndef WTRX_INTERRUPTS
#define WTRX_INTERRUPTS

#include <stdint.h>

// fance()
#define fence() __asm__ volatile ("":::"memory")

/* PART OUTPUT: WRITE */

// write a byte
static inline void outb(uint16_t port, uint8_t val) {
	__asm__ __volatile__("outb %0, %1" :: "a"(val), "Nd"(port));
}

// write a word
static inline void outw(uint16_t port, uint16_t val) {
        __asm__ __volatile__("outw %0, %1" :: "a"(val), "Nd"(port));
}

// write a dword
static inline void outl(uint16_t port, uint32_t val) {
        __asm__ __volatile__("outl %0, %1" :: "a"(val), "Nd"(port));
}

/* PART INTPUT: READ */

// read a byte
static inline uint8_t inb(uint16_t port) {
	uint8_t val;
        __asm__ __volatile__("inb %1, %0" : "=a"(val) : "Nd"(port));
	return val;
}

// read a world
static inline uint16_t inw(uint16_t port) {
        uint16_t val;
        __asm__ __volatile__("inw %1, %0" : "=a"(val) : "Nd"(port));
        return val;
}

// read a dworld
static inline uint32_t inl(uint16_t port) {
        uint32_t val;
        __asm__ __volatile__("inl %1, %0" : "=a"(val) : "Nd"(port));
        return val;
}

/* iowait_function */
static inline void iowait(void) {
	outb(0xED,0);
}


#endif /* WTRX_INTERRUPTS */
