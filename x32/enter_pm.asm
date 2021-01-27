[bits 16]
switch_to_32:
    cli                 ; bye bye bios funcs ):
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_32
[bits 32]
init_32:
    mov ax, DATA_SEG    ; updating regs
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000    ; updating stack
    mov esp, ebp

    call begin_32       ; we did it bois