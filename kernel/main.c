#include <stdint.h>
#include "isr.h"
#include "screen.h"
#include "ports.h"

#define DEBUG __asm__("xchgw %bx, %bx")

void main()
{
	k_print_string(BLACK, WHITE, "Welcome to the Kernel\n", -1, -1);
	k_print_log(SUCCESS,"Booting succeded\n");
	isr_install();
	irq_install();
	while (1);	
}
