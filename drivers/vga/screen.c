#include "screen.h"
#include "ports.h"
#include <stdint.h>

volatile static uint8_t *video_mem = (volatile uint8_t *)VIDEO_ADDRESS;

static void set_cursor(uint16_t offset);
static uint16_t get_cursor(void);
static uint16_t coordToOffset(uint8_t x, uint16_t y); 
static uint8_t offsetToRow(uint16_t offset);
static uint8_t offsetToCol(uint16_t offset);


void set_cursor(uint16_t offset)
{
	offset /= 2;

	port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_HIGH_BYTE);
	port_byte_out(CRTC_VGA_REGISTER_DATA, (unsigned char)(offset >> 8));
	port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_LOW_BYTE);
	port_byte_out(CRTC_VGA_REGISTER_DATA, (unsigned char)(offset & 0xff));

}

uint16_t get_cursor(void)
{
	int offset;

	port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_HIGH_BYTE);
    offset = port_byte_in(CRTC_VGA_REGISTER_DATA) << 8;
    port_byte_out(CRTC_VGA_REGISTER_CTRL, CURSOR_LOW_BYTE);
    offset += port_byte_in(CRTC_VGA_REGISTER_DATA);

    return offset * 2;
}
static uint8_t offsetToRow(uint16_t offset)
{
	return offset / (2 * MAX_COLS);

}
static uint8_t offsetToCol(uint16_t offset)
{
	return (offset - (offsetToRow(offset)*2*MAX_COLS))/2;
}

uint16_t coordToOffset(uint8_t x, uint16_t y)
{
	uint16_t offset;
	
	offset = (MAX_COLS * y *2) + (x*2);

	return offset;

}

void k_print_string(uint8_t background, uint8_t foreground, const char *string, uint8_t x, uint8_t y)
{
	int offset;

	if (x >= 0 && y >= 0) {
		offset = coordToOffset(x, y);
	}
	else {
		offset = get_cursor();
		y = offsetToRow(offset);
		x = offsetToCol(offset);
	}

	while (*string != '\0') {
		k_print_chr(background, foreground, *string++, x , y);
		offset = get_cursor();
		x = offsetToCol(offset);
		y = offsetToRow(offset);
	}

}

void k_print_chr(uint8_t background, uint8_t forefround, const char chr, uint8_t x, uint8_t y)
{
	int offset;

	if (x >= 0 && y >= 0 && x <= MAX_COLS && y <= MAX_ROWS)
		offset = coordToOffset(x, y);
	else
		offset = get_cursor();

	if (chr == '\n')
		offset = coordToOffset(0, y+1);
	else {
		*(video_mem+ offset) = chr;	
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0xf0) | forefround;
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0x0f) | (background << 4);
		
	}
	set_cursor(offset);
}


void k_print_log(uint8_t log_type, const char *string)
{
	k_print_chr(BLACK, WHITE, '[', -1, -1);
	
	switch (log_type) {
		case SUCCESS:
			k_print_string(BLACK, GREEN, "SUCCESS", -1, -1);
			break;
		case WARNING:
			k_print_string(BLACK, YELLOW, "WARNING", -1, -1);
			break;
		case FAILURE:
			k_print_string(BLACK, RED, "FAILED", -1, -1);
			break;
		default:
			break;
	}
	k_print_string(BLACK, WHITE, "] ", -1, -1);
	k_print_string(BLACK, WHITE, string, -1, -1);

}
