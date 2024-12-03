	.section __TEXT,__text
	.global _print
	.p2align 2
_print:
	bl _printf
	.section __TEXT,__text
	.global _main
	.p2align 2
_main:
	adrp x0,wl_str.text@PAGE
	add x0, x0, wl_str.text@PAGEOFF
	bl _print
	mov x0, #0
	bl _exit
wl_str.text:
	.asciz "Hello World!\n"
