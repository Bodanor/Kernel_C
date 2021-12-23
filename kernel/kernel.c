#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main() {
    k_clear_screen();
    k_print_operation_status(info, "Kernel Loaded at 0x8000");
    k_print_operation_status(info, "if you see this, then everything went well");
    k_print_operation_status(info, "Loading the IDT table to enable interrupts");
    isr_install();
    __asm__ __volatile__("int $2");
    k_print_operation_status(success, "IDT Enabled, interrupts working !");
}