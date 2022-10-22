section .data
; 	string~ test = 'test'
 
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


run:

	move  34, rax
	return  0

global main

main:
	
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx; 	syscall

	syscall
	move  60, rax
	move  0, rdi; 	syscall

	syscall