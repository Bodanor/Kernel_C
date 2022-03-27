.intel_syntax noprefix
.code16
secondstage_start:

    mov di, offset flat:protected_mode_switch_msg
    call print_16

    /* Loading the GDT Table */
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    ljmp CODE_SEG:init_pm

    /* End of loading GDT Table */

.include "gdt.S"

/* Beginning of 32 bit code */

.code32
init_pm:
    
    /* After loading the GDT we have to update the segment registers */
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM

BEGIN_PM:
    /**
    * From here, we lose the BIOS Interrupts, so we have rewrite them.
    * So for exemple, Int 0X10 to write text doesn't work anymore
    * Therefore, we call print_32
    **/
    mov edi, offset flat:protected_mode_switch_success
    call print32
    
    mov edi, offset flat:call_kernel_msg
    call print32
    DEBUG
    call 0x9200

    
    
.include "print_32.S"

protected_mode_switch_msg:
    .asciz "Attempting to switch to 32 bit protected mode...\n"

protected_mode_switch_success:
    .asciz "Entered protected mode successfully (32-bit)"

call_kernel_msg:
    .asciz "Giving control to the kernel..."

. = secondstage_start + 512












/*
//Checking for Long mode support (AKA 64 bit CPU)
.check_lm:
    mov eax, 0x80000001
    cpuid
    test edx, (1 << 29)
    jz .lm_error

    mov byte ptr[long_mode_support], 1
    

.lm_error:
  movb [long_mode_support], 0
  mov di, offset flat:lm_error_str
  call print

long_mode_support:
    .int 0
.include "gdt.S"

*/