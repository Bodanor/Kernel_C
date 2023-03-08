#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "screen.h"
#include <stdint.h>

uint32_t tick = 0;

static void timer_callback(registers *regs)
{
	tick++;
}

void init_timer(uint32_t freq)
{
	register_int_handler(IRQ0, timer_callback);
	uint32_t divisor = 1193180 / freq;
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

	port_byte_out(0x43, 0x36);
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}
