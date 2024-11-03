;
; kmain.asm: Call the C'ish main function(execute kmain.c entrypoint)
;
global _start;
[bits 32]

_start:
    [extern kmain]
    call kmain
    jmp $
