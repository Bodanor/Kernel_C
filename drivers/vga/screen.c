#include "screen.h"
#include "ports.h"
#include <stdint.h>

volatile static uint8_t *video_mem = (volatile uint8_t*)VIDEO_ADDRESS;
volatile static uint8_t curr_x, curr_y;

static void set_cursor(uint16_t offset);
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

void k_print_string(uint8_t background, uint8_t foreground, const char *string, int8_t x, int8_t y)
{
	int offset;

	if (x >= 0 && y >= 0 && x <= MAX_COLS && y <= MAX_ROWS) {
		offset = coordToOffset(x, y);
		curr_y = offsetToRow(offset);
		curr_x = offsetToCol(offset);
	}

	while (*string != '\0') {
		k_print_chr(background, foreground, *string++, curr_x , curr_y);
		offset = coordToOffset(curr_x, curr_y);
		curr_x = offsetToCol(offset);
		curr_y = offsetToRow(offset);
	}

}



void k_print_chr(uint8_t background, uint8_t forefround, const char chr, int8_t x, int8_t y)
{
	int offset;
	int i;

	if (x >= 0 && y >= 0 && x <= MAX_COLS && y <= MAX_ROWS){
		offset = coordToOffset(x, y);
		curr_x = x;
		curr_y = y;
	}

	else
		offset = coordToOffset(curr_x, curr_y);

	if (chr == '\n')
		offset = coordToOffset(0, ++curr_y);
	if (chr == 0x08) {
		*(video_mem + offset) = ' ';
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0xf0) | forefround;
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0x0f) | (background << 4);
	}
	else {
		*(video_mem+ offset) = chr;	
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0xf0) | forefround;
		*(video_mem+ offset + 1) = (*(video_mem + offset + 1) & 0x0f) | (background << 4);
		offset+= 2;
	}
	
	if (offset >= MAX_ROWS*MAX_COLS *2) {
		for (i = 1; i < MAX_ROWS; i++)
			memcpy((void*)video_mem + coordToOffset(0, i-1), (void*)video_mem + coordToOffset(0, i), MAX_COLS * 2);

		for (i = 0; i < MAX_COLS * 2; i++)
			((char*)(video_mem + coordToOffset(0, MAX_ROWS-1)))[i] = 0;
		offset -= 2 * MAX_COLS;

	}

	curr_x = offsetToCol(offset);
	curr_y = offsetToRow(offset);
	set_cursor(offset);
}


#define DEBUG __asm__("xchgw %bx, %bx")
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

void k_print_backspace(void)
{
	int offset = coordToOffset(curr_x, curr_y) - 2;
	k_print_chr(BLACK, WHITE, 0x08, offsetToCol(offset), offsetToRow(offset));
}
