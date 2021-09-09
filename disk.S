read_sectors:
    pusha
    /*
    See this link for more info https://stanislavs.org/helppc/int_13-2.html
    */
    mov ah, 0x2     # int 0x13/ah=0x2, read sector into memory
    mov dl, dh      # Is the driver number (0x80 for drive, 0x81 for drive1, etc)
    mov ch, 0x00    # Cylinder number
    mov dh, 0x00    # Head number
    mov cl, 0x2     # Start reading at CL sector (sector 1 = boot sector, sector 2 = right after boot sector)
    
    int 0x13

    jc disk_error

disk_error: