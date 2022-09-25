section .data
;   string~ test = 'test'
 
	 test: db 'test', 0
	.len: equ $- test
section .text



global main

main:
	;   move~ 1, rax
 	mov rax, 1;   move~ 1, rdi
 	mov rdi, 1;   move~ test, rsi
 	mov rsi, test;   move~ test.len, rdx
 	mov rdx, test.len;   syscall

	syscall
	mov rax, 60
	mov rdi,  0

	syscall