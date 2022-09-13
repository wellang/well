section .data

	str: db '%s', 10, 0
; 	string~ test = 'test'
 
	 test : db 'test'
section .text



global main

main:
	
	extern printf
; 	move~ str, rdi 
 	mov rdi , str; 	move~ test, rsi
 	mov rsi, test
	call main.4892print
	jmp main.4892printfin
	.4892print:; 	move~ 0, rax
 	mov rax, 0
	call printf

	.4892printfin:

	mov rax, 60
	mov rdi,  0

	syscall
