[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, msg_16
    call print

    call print_nl

    call load_kernel
    call switch_to_32
    jmp $

%include "x16/disk_mg.asm"
%include "x16/print_s.asm"
%include "x32/gdt_structure.asm"
%include "x32/print.asm"
%include "x32/enter_pm.asm"

[bits 16]
load_kernel:
    mov bx, msg_kernel_control
    call print
    call print_nl

    mov bx, KERNEL_OFFSET ; read from disk and store in 0x1000
    mov dh, 2
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
begin_32:
    mov ebx, msg_32
    call print_32
    call KERNEL_OFFSET ; give control to the kernel !!!
    jmp $ 

    
msg_16 db "Loaded x16", 0
msg_32 db "Loaded x32", 0
msg_kernel_control db "Calling kernel offset..", 0
BOOT_DRIVE db 0 ; good idea to store it in memory because 'dl' may get overwritten


times 510-($-$$) db 0
dw 0xaa55