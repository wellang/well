section .data
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

	mov rax, 60
	mov rdi,  0;

	syscall
