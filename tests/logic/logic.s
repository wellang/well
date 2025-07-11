	.text
	.global main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	movq wl_str_hello(%rip),%rdi
	call printf
	movq wl_int_a(%rip),%rdi
	movq %rdi, %rsi
	notq %rsi
	movq wl_str_ntest(%rip),%rdi
	call printf
	movq wl_int_a(%rip),%rdi
	movq wl_int_b(%rip),%rsi
	movq %rdi, %rdx
	andq %rsi, %rdx
	movq %rdx,%rsi
	movq wl_str_atest(%rip),%rdi
	call printf
	movq wl_int_a(%rip),%rdi
	movq wl_int_b(%rip),%rsi
	movq %rdi, %rdx
	orq %rsi, %rdx
	movq %rdx,%rsi
	movq wl_str_otest(%rip),%rdi
	call printf
	movq wl_int_a(%rip),%rdi
	movq wl_int_b(%rip),%rsi
	movq %rdi, %rdx
	orq %rsi, %rdx
	notq %rdx
	movq %rdx,%rsi
	movq wl_str_notest(%rip),%rdi
	call printf
	movq wl_int_a(%rip),%rdi
	movq wl_int_b(%rip),%rsi
	movq %rdi, %rdx
	andq %rsi, %rdx
	notq %rdx
	movq %rdx,%rsi
	movq wl_str_natest(%rip),%rdi
	call printf
	movl $0, %eax
	addq $16, %rsp
	popq %rbp
	ret
	.text
	.global wl_str_hello
.rawwl_strhello:
	.asciz "- - - Bitwise logic test - - -\n"
	.data
	.align 8
wl_str_hello:
	.quad .rawwl_strhello

	.global wl_int_a
	.p2align 2,0x0
wl_int_a:
	.quad 0x1

	.global wl_int_b
	.p2align 2,0x0
wl_int_b:
	.quad 0x1
	.text
	.global wl_str_ntest
.rawwl_strntest:
	.asciz "NOT:: should be: -2. Is: %d\n"
	.data
	.align 8
wl_str_ntest:
	.quad .rawwl_strntest
	.text
	.global wl_str_atest
.rawwl_stratest:
	.asciz "AND:: should be: 1. Is: %d\n"
	.data
	.align 8
wl_str_atest:
	.quad .rawwl_stratest
	.text
	.global wl_str_otest
.rawwl_strotest:
	.asciz "OR:: Should be: 1. Is: %d\n"
	.data
	.align 8
wl_str_otest:
	.quad .rawwl_strotest
	.text
	.global wl_str_notest
.rawwl_strnotest:
	.asciz "NOR:: Should be: -2. Is: %d\n"
	.data
	.align 8
wl_str_notest:
	.quad .rawwl_strnotest
	.text
	.global wl_str_natest
.rawwl_strnatest:
	.asciz "NAND:: Should be: -2. Is: %d\n"
	.data
	.align 8
wl_str_natest:
	.quad .rawwl_strnatest
