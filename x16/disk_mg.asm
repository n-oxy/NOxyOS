disk_load:
    pusha
    push dx
    mov ah, 0x02    ; number for read sub function
    mov al, dh
    mov cl, 0x02    ; 0x01 = boot sector 0x02 = first loadable sector
    mov ch, 0x00
    mov dh, 0x00    ; disk head number
    int 0x13        ; disk read/write sub function from ah using disk manager from bios (v swag)
    jc disk_error
    pop dx
    cmp al, dh
    jne sector_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl

sector_error:
    mov bx, SECTOR_ERROR
    call print
    call print_nl

DISK_ERROR:
    db "Disk is mad", 0

SECTOR_ERROR:
    db "Bad sector read", 0