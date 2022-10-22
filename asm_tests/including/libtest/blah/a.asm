section .data

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
	
	jmp main._1blah_
	jmp main._1blah_fin
	._1blah_:
	mov rax, 60
	mov rdi,  69420

	syscall
	._1blah_fin:

	return  0;