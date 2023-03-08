#include <stdint.h>
#include "shell.h"
#include "isr.h"
#include "screen.h"
#include "ports.h"
#include "timer.h"
#include "rtc.h"

#define DEBUG __asm__("xchgw %bx, %bx")

extern rtc current_rtc;

void kmain()__attribute__((__section__(".kmain")));

void kmain() 
{
	k_printf("<2> Kernel loaded at -->  %x in physical memory\n", 0x10000);
	k_printf("<0> Booting succeeded\n");
	isr_install();
	irq_install();
	read_rtc();
	k_print_string(BLACK, CYAN, "Welcome to the kernel !\n", -1, -1);
	k_printf("<2> TimeStamp : %d/%d/%d %d:%d:%d\n",current_rtc.day, current_rtc.month, current_rtc.year, current_rtc.hour, current_rtc.minute, current_rtc.second);
	init_shell();
	shell_loop();
}
