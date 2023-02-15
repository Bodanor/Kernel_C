#include "screen.h"
#include "ports.h"
#include <stdint.h>

volatile uint8_t *video_mem = (volatile uint8_t*)VIDEO_ADDRESS;

void k_print_string(uint8_t background, uint8_t foreground, const uint8_t *string)
{
	while (*string != '\0') {
		k_print_chr(background, foreground, string++);
	}

}

void k_print_chr(uint8_t background, uint8_t forefround, const uint8_t *chr)
{
	*video_mem++ = *chr;
	*video_mem = (*video_mem & 0xf0) | forefround;
	*video_mem = (*video_mem & 0x0f) | (background << 4);
	video_mem++;
}

void set_cursor(uint8_t x, uint8_t y)
{


}

