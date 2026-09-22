#ifndef WTRX_TTY_H
#define WTRX_TTY_H

#include "vga.h"

#define tty_backend_print vga_print
#define tty_backend_clear vga_clear

static inline void printf(const char* str) {
    tty_backend_print(str);
}

static inline void clearf(void) {
    tty_backend_clear();
}

#endif /* WTRX_TTY_H */
