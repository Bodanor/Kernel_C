#include "screen.h"
#include "ports.h"
#include <stdint.h>

#define DEBUG __asm__("xchgw %bx, %bx")

void main()
{
	k_print_init();
	k_print_string(BLACK, WHITE, (uint8_t*)"Welcome to the Kernel\n");
	k_print_log(SUCCESS,(uint8_t*)"Booting succeded\n");
	while (1);	
}
