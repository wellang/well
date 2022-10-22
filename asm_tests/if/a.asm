section .data
;           string~ test = 'test'
 
	 test: db 'test', 0
	.len: equ $- test
section .text

%macro move 2

	mov %2, %1

%endmacro
%macro pop 1

	pop %1

%endmacro
%macro add 2

	add %2, %1

%endmacro
%macro sub 2

	sub %2, %1

%endmacro
%macro xor 2

	xor %2, %1

%endmacro
%macro return 1

	move  60, rax
	move  %1, rdi;                syscall

	syscall
%endmacro

section .text



global main

main:
	
	move  1, rbp
	move  1, rsp
	move  5, r8
	move  4, r9
	cmp rbp, rsp
	je main._15_1rbprsp_eq
	jne main._15_1_fin
	._15_1rbprsp_eq:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx;                    syscall

	syscall
	jmp main._15_1_fin
	._15_1_fin:
	cmp r8, r9
	jne main._25_2r8r9_neq
	je main._25_2_fin
	._25_2r8r9_neq:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx; 	                syscall

	syscall
	jmp main._25_2_fin
	._25_2_fin:
	cmp r8, r9
	jg main._35_3r8r9_gre
	jng main._35_3_fin
	._35_3r8r9_gre:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx; 	                syscall

	syscall
	jmp main._35_3_fin
	._35_3_fin:
	cmp r9, r8
	jl main._45_4r9r8_les
	jnl main._45_4_fin
	._45_4r9r8_les:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx;                     syscall

	syscall
	jmp main._45_4_fin
	._45_4_fin:
	return  0