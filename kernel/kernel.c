// kernel
#include "kernel.h"

// call the lib tty.h
#include "tty.h"

// call all interrupts
#include "gdt.h"
#include "idt.h"
#include "pic.h"

void wtrx_main(void) {
	clearf();

	gdt_install();
	printf("[ OK ] GDT is to far\n");

	idtinstall();
	printf("[ OK ] IDT is deleted\n");

	picremap(0x20, 0x28);
	printf("[ OK ] PIC NOT FOUND!\n");

	printf("[INFO] TTY initialized (backend: VGA text mode)\n");
        printf("[SUCCESS] WTRX IS BOOT!\n");
}
