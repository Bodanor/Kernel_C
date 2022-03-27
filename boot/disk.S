.intel_syntax noprefix
.code16

/*
 * AH : Read Disk Sectors
 * AL = number of sectors to read
 * CH = Track/cylinder number
 * CL = Sector Number (our bootloader is the 1 one, so we start reading at sector 2)
 * DH = Head number
 * DL = Drive number -->  Floppy A = 0, Drive 1 = 0x80, Drive 2 = 0x80, ...
 * ES:BX = Pointer to buffer
 */

/**
* This function receives the drive number to read data from
* into register DX, therefore we push DX in order to compare
* after reading sectors if the correct numbers of sectors
* have been read.
*/
readDisk:
    pusha
    push dx

    mov dl, 0
    mov ah,0x02
    mov ch, 0x0
    mov cl, 0x2
    mov al, dh
    mov dh, 0

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret

disk_error:

    mov di, offset flat:DISK_ERROR_MSG
    call print_16
    jmp .die

sectors_error:
    mov di, offset flat:SECTORS_ERROR
    call print_16
    jmp .die

.die:
    popa
    hlt

DISK_ERROR_MSG:
    .asciz "Disk read error. Dying\n"

SECTORS_ERROR:
    .asciz "Incorrect number of sectors read. Dying\n"


