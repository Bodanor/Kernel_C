.intel_syntax noprefix
.code16
.section .stage2, "ax"

    mov si, offset flat:DE_msg
    call print_16
    jmp .
DE_msg:
    .asciz "Hello From stage 2"
