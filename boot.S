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



    /*
    Switching resolution here and disabling the blinking cursor just for the fun of it :)
    */
    mov ah, 0
    mov al, 0x3
    int 0x10

    mov ah, 0x01
    mov ch, 0x3f
    int 0x10

    mov si, offset flat:switchedResSuccessMSG
    mov bl, 0x1f    #Character attribute (White on Blue)
    call printStr

    /*
    We are verifying the value on DL so see if it's a buggy BIOS or not 
    */
    cmp dl, 80
    jb badDrive
    

    cmp dl, 0x8f
    ja badBoot

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
    The reason why it didn't worked before was beacause switching to `12  640x480 16 color graphics (VGA)` causes
    the video address memeory to change from 0xb000 to 0xa000. 640x480x16 is a graphics mode, a planar one. color text isn't
    the same as color graphics!
    */
    mov ah, 0x09
    mov bh, 0x0
    mov cx, 0x1


    int 0x10
    /*
    I use int 0x10 again but with the write in teletext function as using int 0x10 with ah = 0x9 doesn't move the cursor
    */
    mov ah, 0x0e
    int 0x10

    add si, 1 # Increment till al = 0 (AKA end of the string)
    jmp printLoop

printEnd:

    /*
    Eveerytime we exit this function, we want to print a NewLine
    */
    mov ah, 0x0e
    mov al, 0x0a 
    int 0x10
    mov al, 0x0d
    int 0x10
    /*
    Don't forget to get the values of every register back before this function was called!
    */
    popa
    ret

err:
    push 0xb800
    pop es
    .h:hlt
    jmp .h

badDrive:
    mov si, offset flat:badDriveMsg
    mov bl, 0x4f
    call printStr
    jmp err

badBoot:
    mov si, offset flat:badBootMSG
    mov bl, 0x4f
    call printStr
    jmp err

switchedResSuccessMSG:
    .asciz "Switched to 80x25 16 color text !"

badDriveMsg:
    .asciz "Bad Drive Number given from the BIOS! Restarting in 5 seconds"

badBootMSG:
    .asciz "An error occured at the booting process! Restarting in 5 seconds"

. = _start + 510 # Filling up space to match 512 bytes as the next MAGIC number must be at the 512th byte.
.word 0xaa55 # This is the MAGIC numebr for the MBR. It must always be this value !
