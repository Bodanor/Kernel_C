.intel_syntax noprefix
.code16
.section .stage2, "ax"

/* This is a macro to place a breakpoint with bochs */
.macro DEBUG
xchg bx, bx
.endm


try_13h_extend_support:
    /* Test if INT 13 Extensions works */
    mov ah, 0x41
    mov bx, 0x55AA
    mov dl, byte ptr[BOOT_DISK]
    int 0x13
    jc int13h_extend_fail

    mov si, offset flat:int13_extend_supported_msg
    call print_16
    
    mov si, offset flat:loading_kernel_msg
    call print_16
    push cx
    xor cx, cx
    
load_sectors:
    clc
    
    cmp word ptr[DAP + 6], 0
    je increment_segment
    mov dl, byte ptr[BOOT_DISK]
    mov ah, 0x42
    mov si, offset flat:DAP
    int 0x13
    jc done_sectors
   
    add word ptr[DAP + 4], 512
increment_value:
    xor ebx, ebx
    inc dword ptr[DAP + 8]
    seto bl
    add dword ptr[DAP + 12], ebx
    inc cx
    jmp load_sectors

increment_segment:
    add word ptr[DAP + 6], 0x1000
    jmp load_sectors

done_sectors:
    mov si, cx
    call print_hex
    mov si, offset flat:loaded_sectors
    call print_16
    jmp .

DAP:
    .byte 0x10
    .byte 0x0
    .short 0x1
    .short 0x9000
    .short 0x0
    .quad 2
    .quad 0

loaded_sectors:
    .asciz " Sectors loaded.\n"

loading_kernel_msg:
    .asciz "Loading Kernel at address 0x10000...\n"

int13h_extend_fail:
    mov si, cx
    call print_hex
    mov si, offset flat:int13h_extend_fail_msg
    call print_16
    hlt
    jmp .

int13_extend_supported_msg:
    .asciz "BIOS supports INT 13 Extended mode.\n"

int13h_extend_fail_msg:
    .asciz "Bios does not support INT13 Extended mode\nCan't continue to boot...\n"
. = try_13h_extend_support + 512

