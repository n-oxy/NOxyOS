[bits 32]
[extern _start]		; define calling point. must have same name as kernel.c 'start' function
call _start			; calls c function
jmp $