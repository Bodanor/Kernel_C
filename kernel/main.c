#include <stdint.h>
#include "shell.h"
#include "isr.h"
#include "screen.h"
#include "ports.h"
#include "timer.h"
#include "rtc.h"

#define DEBUG __asm__("xchgw %bx, %bx")

rtc boot_rtc_time;
void kmain()__attribute__((__section__(".kmain")));

void kmain() 
{
	k_printf("<2> Kernel loaded at -->  %x in physical memory\n", 0x10000);
	k_printf("<0> Booting succeeded\n");
	isr_install();
	irq_install();
	read_rtc(&boot_rtc_time);
	k_print_string(BLACK, CYAN, "Welcome to the kernel !\n", -1, -1);
	k_printf("<2> TimeStamp : %d/%d/%d %d:%d:%d\n",boot_rtc_time.day,boot_rtc_time.month, boot_rtc_time.year, boot_rtc_time.hour, boot_rtc_time.minute, boot_rtc_time.second);
	init_shell();
	shell_loop();
}
