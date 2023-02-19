#include "idt.h"
#include <stdint.h>

struct __attribute__((packed)) idt_gate_t {
	uint16_t low_offset;
	uint16_t selector;
	uint8_t always0;
	uint8_t flags;
	uint16_t high_offset;
};

struct __attribute__((packed)) idt_ptr_t {
	uint16_t limit;
	uint32_t base;
};

static idt_gate idt[IDT_ENTRIES];
static idt_ptr idt_pt;

void set_idt_gate(int n, uint32_t handler)
{
	idt[n].low_offset = handler & 0xffff;
	idt[n].selector = KERNEL_CS;
	idt[n].always0 = 0;
	idt[n].flags = 0x8e;
	idt[n].high_offset = (handler >> 16) & 0xffff;
}

void set_idt_cpu(void)
{
	idt_pt.base = (uint32_t) &idt;
	idt_pt.limit = IDT_ENTRIES *sizeof(idt_gate) -1;
	__asm__("lidtl (%0)" : : "r" (&idt_pt));

}
