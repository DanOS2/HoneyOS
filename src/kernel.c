/*
HoneyOS 0.2 11.09.2021
Created by Daniil Lebedev
GitHub https://github.com/DanOS2/HoneyOS/releases
*/
#include "include/tty.h"
#include "include/keyboard.h"

void kernel_main(){
	t_init(); // initialize the screen to get started and clear it
    t_set_color(VGA_COLOR_LIGHT_MAGENTA);
    t_print("********************************************************************************\n");
    t_print("                                  HoneyOS v0.2                                  \n");
    t_print("********************************************************************************\n");
    t_print("\n");
    t_set_color(VGA_COLOR_LIGHT_GREEN);
    t_print("$ ");
    t_set_color(VGA_COLOR_LIGHT_GREY);
    keyboard_init();
    while(true){
        keyboard_handler();
    }
    while(true);
}