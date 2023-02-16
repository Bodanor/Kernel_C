#include "screen.h"
#include "ports.h"
#include <stdint.h>

volatile uint8_t *video_mem;
volatile uint8_t x, y;

void k_print_init(void)
{
	video_mem = (volatile uint8_t*)VIDEO_ADDRESS;
	x = y = 0;
}

void k_print_string(uint8_t background, uint8_t foreground, const uint8_t *string)
{
	while (*string != '\0') {
		k_print_chr(background, foreground, *string++);
	}

}

void k_print_chr(uint8_t background, uint8_t forefround, const uint8_t chr)
{
	if (x == MAX_COLS) {
		x = 0;
		++y;
	}
	if (y == MAX_ROWS && x == MAX_COLS) {
		y = x = 0;
		video_mem = (volatile uint8_t*)VIDEO_ADDRESS;
	}

	if (chr == '\n') {
		video_mem += (++y*MAX_COLS - x) *2;
		set_cursor(0, y);
	}
	else {
	*video_mem++ = chr;
	*video_mem = (*video_mem & 0xf0) | forefround;
	*video_mem = (*video_mem & 0x0f) | (background << 4);
	video_mem++;
	set_cursor(++x, y);
	
	}
}

void set_cursor(uint8_t x, uint8_t y)
{
	int position;

	position = x+ (MAX_COLS*y);

	port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_HIGH_BYTE);
	port_byte_out(CRTC_VGA_REGISTER_DATA, (unsigned char)(position >> 8));
	port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_LOW_BYTE);
	port_byte_out(CRTC_VGA_REGISTER_DATA, (unsigned char)(position & 0xff));

}

void k_print_log(uint8_t log_type, const uint8_t *string)
{
	k_print_chr(BLACK, WHITE, (uint8_t)'[');
	
	switch (log_type) {
		case SUCCESS:
			k_print_string(BLACK, GREEN, (uint8_t*)"SUCCESS");
			break;
		case WARNING:
			k_print_string(BLACK, YELLOW, (uint8_t*)"WARNING");
			break;
		case FAILURE:
			k_print_string(BLACK, RED, (uint8_t*)"FAILED");
			break;
		default:
			break;
	}
	k_print_string(BLACK, WHITE, (uint8_t*)"] ");
	k_print_string(BLACK, WHITE,  (uint8_t*)string);

}
