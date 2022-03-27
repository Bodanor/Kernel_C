.intel_syntax noprefix
.code32

.equ VIDEO_BUFFER, 0xb8000
.equ WHITE_ON_BLACK, 0x0f
print32:
    pusha

    mov edx, VIDEO_BUFFER
print_32_loop:
    mov al, byte ptr[edi]
    mov ah, WHITE_ON_BLACK
    cmp al, 0
    je print32_end
    mov word ptr[edx], ax
    add di, 1
    add edx, 2
    jmp print_32_loop


print32_end:
    popa
    ret
