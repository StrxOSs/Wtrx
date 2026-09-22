#ifndef WTRX_VGA_H
#define WTRX_VGA_H

#include <stdint.h>

#define VGA_ADDRESS     0xB8000
#define VGA_WIDTH       80
#define VGA_HEIGHT      25
#define VGA_COLOR_DEF   0x0F

void vga_clear(void);
void vga_putchar(char c);
void vga_print(const char* str);

#endif /* WTRX_VGA_H */
