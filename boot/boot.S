.intel_syntax noprefix
.code16

.text
.section .stage1, "ax"

/* This is a macro to place a breakpoint with bochs */
.macro DEBUG
xchg bx, bx
.endm

_start:
    jmp _start_16
    nop
    .space 59, 0    // Faking the BPB again...

_start_16:
    ljmp 0x0000:_init

_init:
    cld // Disable interrupts while we setup the stack

    mov bp, 0x9000  // Far away from 0x7c00
    mov sp, bp

    xor ax, ax
    mov es, ax
    mov ss, ax
    mov ds, ax
    mov fs, ax
    mov gs, ax

    cli

    mov byte ptr[init_disk], dl //Saving the drive number to load code from with INT 0X13.
    mov di, offset flat:init_msg
    call print_16
    mov di, offset flat:init_disk_msg
    call print_16
    mov bx, 0x9000
    mov dh, 10
    call readDisk

    mov di, offset flat:init_disk_success
    call print_16
    
    mov di, offset flat:init_second_stage_jmp_msg
    call print_16
    ljmp 0x0000:secondstage_start
    

    
.include "print_16.S"
.include "disk.S"

init_disk:
    .int 0

init_msg:
    .asciz "Initial boot !\n"

init_disk_msg:
    .asciz "Loading disk into memory...\n"

init_disk_success:
    .asciz "Disk loaded at offset 0X8000\n"

init_second_stage_jmp_msg:
    .asciz "Jumping to second stage at offset 0X8000\n"

. = _start + 510

.word 0xAA55
.section .stage2, "ax"
.include "secondStage.S"
