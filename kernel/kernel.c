#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "shell.h"

void main() {

    char *prompt = "Kernel~# ";
    char *input;
    k_clear_screen();
    k_print_operation_status(info, "Kernel Loaded at 0x8000");
    k_print_operation_status(info, "if you see this, then everything went well");
    k_print_operation_status(info, "Loading the IDT table to enable interrupts");
    isr_install();
    k_print_operation_status(success, "IDT Enabled, interrupts working !");
    irq_install();

    while (1)
    {
        input = k_shell_prompt(prompt);
        k_shell_verify_cmd(input);        
    }

}