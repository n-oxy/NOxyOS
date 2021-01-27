[bits 32]
VID_MEM equ 0xb8000
W_B equ 0x0f
print_32:
    pusha
    mov edx, VID_MEM

print_internal_32:
    mov al, [ebx]
    mov ah, W_B

    cmp al, 0
    je print_ret_32

    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp print_internal_32
print_ret_32:
    popa
    ret