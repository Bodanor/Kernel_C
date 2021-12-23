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



print_hex:
    pusha

    mov cx, 0 

hex_loop:
    cmp cx, 4
    je end2
    

    mov ax, dx 
    and ax, 0x000f 
    add al, 0x30 
    cmp al, 0x39 
    jle step2
    add al, 7 

step2:
    
    mov bx, HEX_OUT + 5
    sub bx, cx
    mov byte ptr[bx], al
    ror dx, 4

    add cx, 1
    jmp hex_loop

end2:
   
    mov bx, offset flat:HEX_OUT
    call print

    popa
    ret

HEX_OUT:
    .asciz "0x0000"
