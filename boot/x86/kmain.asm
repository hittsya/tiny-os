;
; kmain.asm: Call the C'ish main function(execute kmain.c entrypoint)
;

[bits 32]
[extern main]
call main
jmp $
