
.intel_syntax noprefix
.code16 # use 16 bits
switch_to_protected_mode:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    ljmp CODE_SEG:init_pm
    
.code32
init_pm:
    
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x9000
    mov esp, ebp

    call BEGIN_PM


