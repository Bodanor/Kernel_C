.code16
.intel_syntax noprefix
print:
    pusha

print_loop:
    mov al, byte ptr[bx]
    mov ah, 0x0e
    cmp al, 0
    je print_nl

    int 0x10
    add bx, 1
    jmp print_loop

print_nl:
    mov al, 0xa # newline
    mov ah, 0x0e
    int 0x10

    mov al, 0xd # Carriage return
    mov ah, 0x0e
    int 0x10

    jmp end
end:
    popa
    ret
