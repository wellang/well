	.section __TEXT,__text

	.global _main
	.p2align 2

_main:
	adrp x0, str_.text@PAGE
	add x0, x0, str_.text@PAGEOFF
	bl _printf
	mov x0, #0
	bl _exit

str_.text:
	.asciz "hello world!\n"
