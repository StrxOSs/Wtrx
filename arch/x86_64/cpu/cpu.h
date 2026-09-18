#ifndef WTRX_CPU_CONTROL
#define WTRX_CPU_CONTROL

// function hlt(): Halt the cpu
static inline void hlt(void) {
	__asm__ __volatile__("hlt");
}

// function sti(): Cpu Enable Interrupts
static inline void sti(void) {
        __asm__ __volatile__("sti");
}

// function cli(): Cpu Disable Interrupts
static inline void cli(void) {
        __asm__ __volatile__("cli");
}

// function hang(): Cpu Disable Interrupts  && halt the cpu
static inline void hang(void) {
        cli();
	for(;;) {
		hlt();
	}
}

#endif /* WTRX_CPU_CONTROL */
