#include <stdint.h>
#include "shell.h"
#include "isr.h"
#include "screen.h"
#include "ports.h"
#include "timer.h"

#define DEBUG __asm__("xchgw %bx, %bx")
void kmain()__attribute__((__section__(".kmain")));

void kmain() 
{
	k_printf("<2> Kernel loaded at -->  %x in physical memory\n", 0x10000);
	k_printf("<0> Booting succeeded\n");
	isr_install();
	irq_install();
	k_print_string(BLACK, CYAN, "Welcome to the kernel !\n", -1, -1);
	wait_timer(1000);
	init_shell();
	shell_loop();
}
