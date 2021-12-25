load_disk:
    pusha

    push dx


    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00

    int 0x13

    jc disk_error

    pop dx

    cmp al, dh
    jne sectors_error

    popa
    ret

disk_error:
    mov bx, offset flat:disk_error_str
    call print
    hlt
    

sectors_error:
    mov bx, offset flat:sectors_error_str
    call print
    hlt

disk_error_str:
    .asciz "Disk read error"

sectors_error_str:
    .asciz "Incorrect number of sectors read"
    