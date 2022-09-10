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
 	mov rsi, test; 	move~ 0, rax
 	mov rax, 0
 call printf


	mov rax, 60
	mov rdi, 0
	syscall
