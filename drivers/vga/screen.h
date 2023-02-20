#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>
#include "ports.h"
#include "stdlib.h"

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
#define CRTC_VGA_REGISTER_CTRL 0x3D4
#define CRTC_VGA_REGISTER_DATA 0x3D5

#define SUCCESS 0
#define WARNING 1
#define FAILURE 2

void k_print_string(uint8_t background, uint8_t foreground, const char *string, int8_t x, int8_t y);
void k_print_chr(uint8_t background, uint8_t forefround, const char chr, int8_t x, int8_t y);
void k_print_log(uint8_t log_type, const char *string);

#endif
