.intel_syntax noprefix
.code16
.section .stage1, "ax"

/* This is a macro to place a breakpoint with bochs */
.macro DEBUG
xchg bx, bx
.endm

_start:
    jmp _start_16
    nop
    .space 59, 0

_start_16:
    ljmp 0x0000:_init

_init:
    
    /* Init registers and stack */
    cld

    xor ax, ax
    mov es, ax
    mov fs, ax
    mov ss, ax
    mov gs, ax
    mov ds, ax
    
    mov bp, 0x8000
    mov sp, bp

    cli
    /* End of initilization */
    
    mov byte ptr[BOOT_DISK], dl
    
    mov si, offset flat:init_msg
    call print_16
    
    mov si, offset flat:stack_address_msg
    call print_16

    mov si, bp
    call print_hex

    mov si, offset flat:newline_str
    call print_16

    mov si, offset flat:disk_id_msg
    call print_16

    xor dx, dx
    mov dl, byte ptr[BOOT_DISK]
    mov si, dx
    call print_hex

    mov si, offset flat:newline_str
    call print_16

    mov si, offset flat:loading_stage2_msg
    call print_16
    
    mov ah, 0x2
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, byte ptr[BOOT_DISK]
    mov bx, 0x9000
    int 0x13
    jc stage2_failed
    jmp 0x9000
    
stage2_failed:
    mov si, offset flat:stage2_failed_msg
    call print_16
    hlt

init_msg:
    .asciz "POST Completed\nInitialization...\n"

stack_address_msg:
    .asciz "Stack set at : "

disk_id_msg:
    .asciz "Disk id is : "
    
loading_stage2_msg:
    .asciz "Loading Stage2...\n"

stage2_failed_msg:
    .asciz "Failed to load Stage2... Please reboot !\n"

stage2_loaded_msg:
    .asciz "Jumping to Stage 2 loaded at memory address 0x9000 !\n"

newline_str:
    .asciz "\n"

BOOT_DISK:
    .int 0
