section .data ;variables & data not implimented yet

; 	string~ string = 'string!'
 
	 string : db 'string!', 10
	 string_length: equ $- string
	 number: dw 256
	 num_length: equ $- number
section .text

global _start

_start:
	; 	move~ 1, rax
 	mov rax, 1; 	move~ 1, rdi
 	mov rdi, 1; 	move~ string, rsi
 	mov rsi, string; 	move~ string_length, rdx
 	mov rdx, string_length; 	return

	syscall; 	move~ 1, rax
 	mov rax, 1; 	move~ 1, rdi
 	mov rdi, 1; 	move~ number, rsi
 	mov rsi, number; 	move~ num_length, rdx
 	mov rdx, num_length; 	return

	syscall; 	move~ 60, rax
 	mov rax, 60; 	move~ 0, rdi
 	mov rdi, 0; 	return

	syscall