#include "../drivers/screen.h"

void main() {
    k_clear_screen();
    k_print_welcome_label("Kernel 0.0.0", 0x4f, "Dev -> Liwinux", 0x2f);

    k_print_operation_status(info, "Kernel Loaded at 0x8000");
    k_print_operation_status(info, "if you see this, then everything went well");
}