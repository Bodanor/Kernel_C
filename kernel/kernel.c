#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "kernel.h"
#include "../libc/string.h"

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        k_print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    k_print("You said: ");
    k_print(input);
    k_print("\n> ");
}

void main() {
    k_clear_screen();
    k_print_operation_status(info, "Kernel Loaded at 0x8000");
    k_print_operation_status(info, "if you see this, then everything went well");
    k_print_operation_status(info, "Loading the IDT table to enable interrupts");
    isr_install();
    k_print_operation_status(success, "IDT Enabled, interrupts working !");
    irq_install();
}