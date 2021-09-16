#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "ports.h"
#include "vga.h"

void t_set_color(uint8_t c_set);
void t_init();
void t_putch(char c);
void t_print(const char* str);
void t_putint(int i);
void update_cursor();
void t_scroll();
void shutdown();
void printf(const char * s, ...);