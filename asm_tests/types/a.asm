section .data
; 	string~ string = 'string!'
 
	 string: db 'string!', 0
	.len: equ $- string
	 number: dw 25
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
	
	move  1, rax
	move  1, rdi
	move  string, rsi
	move  string.len, rdx; 	syscall

	syscall
	move  60, rax
	move  0, rdi; 	syscall

	syscall
	return  0