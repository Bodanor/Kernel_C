#ifndef __IDT_H__
#define __IDT_H__

#include <stdint.h>

#define IDT_ENTRIES 256
#define KERNEL_CS 0x8

typedef struct idt_gate_t idt_gate;
typedef struct idt_ptr_t idt_ptr;

void set_idt_gate(int n, uint32_t handler);
void set_idt_cpu(void);

#endif
