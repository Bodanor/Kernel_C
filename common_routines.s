.intel_syntax noprefix
.code16

.section .common_rountines, "ax"
.global print_16
.global print_hex

print_16:
    pusha
    
    mov ah, 0x0e

.print_16_loop:
    mov al, byte ptr[si]
    cmp al, 0
    je print_done
    cmp al, 0xa
    je print_nl
    int 0x10
    inc si
    jmp .print_16_loop

print_nl:
    mov al, 0xa
    int 0x10
    mov al, 0xd
    int 0x10
    inc si
    jmp .print_16_loop

print_done:
    popa
    ret

print_hex:
    pusha

    mov cx, 0

.print_hex_loop:
    cmp cx, 4
    je end_hex_loop

    mov ax, si
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle update_hex
    add al, 7

update_hex:
    mov bx, offset flat:HEX + 5
    sub bx, cx
    mov byte ptr[bx], al
    ror si, 4

    inc cx
    jmp .print_hex_loop

end_hex_loop:
    mov si, offset flat:HEX
    call print_16
    
    popa
    ret
HEX:
    .asciz "0x0000"
