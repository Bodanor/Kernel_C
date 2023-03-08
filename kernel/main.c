#include <stdint.h>
#include "shell.h"
#include "isr.h"
#include "screen.h"
#include "ports.h"

#define DEBUG __asm__("xchgw %bx, %bx")
void kmain()__attribute__((__section__(".kmain")));

void kmain() 
{
	k_print_string(BLACK, WHITE, "Welcome to the Kernel\n", -1, -1);
	k_print_log(SUCCESS,"Booting succeded\n");
	isr_install();
	irq_install();
	init_shell();
	shell_loop();
}
