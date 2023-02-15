#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>
#include "ports.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

/* Define usefull colors */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define YELLOW 14
#define WHITE 15

/* Define usefull I/O ports */
#define CURSOR_HIGH_BYTE 14
#define CURSOR_LOW_BYTE 15
#define CRTC_VGA_REGISTER 0x3D4

void k_print_string(uint8_t background, uint8_t foreground, const uint8_t *string);
void k_print_chr(uint8_t background, uint8_t forefround, const uint8_t *chr);
void set_cursor(uint8_t x, uint8_t y);

#endif
