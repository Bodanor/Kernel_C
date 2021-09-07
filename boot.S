.code16
.text
.globl _start, _init
.intel_syntax noprefix

_start:
    jmp bpb_end # Workaround for BIOSes that require a jmp instruction at the beginning..
    nop 

    /*
    Some BIOSes require a BPB and they tend to overwrite byte. We must AVOID that
    or bad things will appen as he code will be overwriten... The workaround
    is to fake a BPB by filling 80 bytes with 0's (AKA .org instruction) 
    */
    .org 80 

bpb_end:
    # Clearing the interrupt and direction flag
    cli 
    cld
    jmp 0x0000:_init

_init:
    /*
    Some BIOSes, give a value to the stack segment register by default
    but we don't know where this is. So we better have to give a value
    by our selfs and re-enable the interrupt flag 
    */

    xor ax, ax # Xoring by the same register is = 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00


    # We will disable the blinking cursor here:
    mov ah, 0x01
    mov ch, 0x3f
    int 0x10

    

afterSwitched:
    mov si, offset flat:switchedModeMSG
    mov bl, 0xF3
    call printStr
    jmp .


printStr:
    pusha

printLoop:
    mov al, byte ptr[si]
    cmp al, 0
    je printEnd

    /*
    Here I'm using ah = 0x09 because we have the choice to set character attributes (background and foreground color) when calling
    this function (just to flex :))
    */
    mov ah, 0x09
    mov bh, 0x0
    mov cx, 0x1


    int 0x10
    /*
    I use int 0x10 again but with to write in teletext as using int 0x10 with ah = 0x9 doesn't move the cursor
    */
    mov ah, 0x0e
    int 0x10

    add si, 1 # Increment till al = 0 (AKA end of the string)
    jmp printLoop

printEnd:
    popa
    ret

switchedModeMSG:
    .asciz "Switched to 640x480 16 color graphics (VGA) mode !"

. = _start + 510 # Filling up space to match 512 bytes as the next MAGIC number must be at the 512th byte.
.word 0xaa55 # This is the MAGIC numebr for the MBR. It must always be this value !
