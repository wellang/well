section .data
;           string~ test = 'test'
 
	 test : db 'test'
	 tl: equ $- test
section .text



global main

main:
	;     move~ 1, rbp
 	mov rbp, 1;     move~ 1, rsp
 	mov rsp, 1
	cmp rbp, rsp
	je main.8839rbprspeq
	jne main.8839fin
	.8839rbprspeq:;         move~ 1, rax
 	mov rax, 1;         move~ 1, rdi
 	mov rdi, 1;         move~ test, rsi
 	mov rsi, test;         move~ tl, rdx
 	mov rdx, tl;         syscall

	syscall
	jmp main.8839fin
	.8839fin:
	mov rax, 60
	mov rdi,  0

	syscall
