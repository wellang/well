section .data

	str: db '%s', 10, 0
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



global main

main:
	
	extern printf

	move  str, rdi 
	move  test, rsi
	jmp main._1print_
	jmp main._1print_fin
	._1print_:; 	move~ 0, rax
 	mov rax, 0
	call printf

	ret

	jmp main._1print_fin
	._1print_fin:

	return  0