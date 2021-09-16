#include "../include/tty.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;

const int VGA_COLS = 80;
const int VGA_ROWS = 25;

int t_col = 0;
int t_row = 0;

size_t tty_line_fill[VGA_HEIGHT];
uint8_t t_color = VGA_COLOR_LIGHT_GREY;

// initialize the screen to get started and clear it
void t_init(){
    for (int col = 0; col < VGA_COLS; col++){
        for (int row = 0; row < VGA_ROWS; row++){
            size_t index = (VGA_COLS * row) + col;
            vga_buffer[index] = ((uint16_t)t_color << 8) | ' ';
        }
    }
}

// turns off the computer
void shutdown(){
    outw(0xB004, 0x2000);
    outw(0x604, 0x2000);
    outw(0x4004, 0x3400);
}

// set color for text and background
// VGA table in file vga.h
void t_set_color(uint8_t c_set){
    t_color = c_set;
}

// update the cursor to be at the end of the text
void update_cursor(){
    unsigned short position = (t_row * VGA_WIDTH) + t_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

// we place a record with the data indicated by us
void t_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    vga_buffer[index] = vga_entry(c, color);
}

// so that if the text is below the screen, then go to it
void t_scroll() {
  t_row--;
  for (size_t y = 0; y < VGA_HEIGHT - 1; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t src_index = y * VGA_WIDTH + x;
      const size_t dstty_index = (y + 1) * VGA_WIDTH + x;
      vga_buffer[src_index] = vga_buffer[dstty_index];
    }
    tty_line_fill[y] = tty_line_fill[y + 1];
  }

  for (size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
    vga_buffer[index] = vga_entry(' ', t_color);
  }
}

// character output
void t_putch(char c){
    if (c != '\n') {
        t_putentryat(c, t_color, t_col, t_row);
    } 

    if (++t_col == VGA_WIDTH || c == '\n') {
        tty_line_fill[t_row] = t_col - 1;
        t_col = 0;
        if (++t_row == VGA_HEIGHT) {
            t_scroll();
        }
    }
    update_cursor();
}

// line output
void t_print(const char* str){
    for (size_t i = 0; str[i] != '\0'; i++) t_putch(str[i]);
}

// non-standard number output
void t_putuint(int i){
    unsigned int n, d = 1000000000;
    char str[255];
    unsigned int dec_index = 0;

    while ((i/d == 0) && (d >= 10)){
        d /= 10;
    }
    n = i;
    while (d >= 10){
        str[dec_index++] = ((char)((int)'0' +n/d));
        n = n % d;
        d /= 10;
    }
    str[dec_index++] = ((char)((int)'0' +n));
    str[dec_index] = 0;
    t_print(str);
}

// number output
void t_putint(int i){
    if (i >= 0){
        t_putuint(i);
    } else {
        t_putch('-');
        t_putuint(-i);
    }
}