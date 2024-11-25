; this SHOULD be the output from the wellang compiler

.section __TEXT,__text

.global _main
.p2align 2
; this is without cfi debug markers
; I'm not sure if or when I'll add that into the compiler
_main:
	adrp x0, str_.text@PAGE ; load address of text into register
	add x0, x0, str_.text@PAGEOFF ; load the offset 12-bits of text
	bl _printf ; call~ printf
	mov x0, #0
	bl _exit

str_.text: ; text is the name of the variable in the well file
	.asciz "Hello World!\n"

