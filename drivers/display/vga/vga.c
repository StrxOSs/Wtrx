#include "vga.h"

static uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;
static int cursor_x = 0;
static int cursor_y = 0;

void vga_clear(void) {
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga_buffer[i] = (VGA_COLOR_DEF << 8) | ' ';
	}
	cursor_x = 0;
	cursor_y = 0;
}

void vga_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    int index = cursor_y * VGA_WIDTH + cursor_x;
    vga_buffer[index] = (VGA_COLOR_DEF << 8) | c;

    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

void vga_print(const char* str) {
	while (*str) {
		vga_putchar(*str++);
	}
}
