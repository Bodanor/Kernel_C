.intel_syntax noprefix
.code16 


/*
    AH : 0x0e --> Teletype
    To function receives the string to print in the register DI

*/
print_16:
    pusha

    mov ah, 0x0e
print_loop:

    mov al, byte ptr[di]
    cmp al, 0       // If null terminator, then end
    je print_end
    cmp al, 0xa     // If newline
    je print_newline
    int 0x10
    inc di          //Don't forget to increment
    jmp print_loop

print_newline:
    mov al, 0xa     // print newline + carriage return
    int 0x10
    mov al, 0xd
    int 0x10
    inc di          //Don't forget to increment
    jmp print_loop

print_end:
    popa
    ret