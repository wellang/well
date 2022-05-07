section .data ;variables & data not implimented yet

; string~ text = 'test'
 
	 text : db 'test', 10
	 text_length: equ $- text
section .text

global _start

_start:
	; move~ 1, rax
 	mov rax, 1; move~ 1, rdi
 	mov rdi, 1; move~ text, rsi
 	mov rsi, text; move~ text_length, rdx
 	mov rdx, text_length; return

	syscall; move~ 60, rax
 	mov rax, 60; move~ 0, rdi 
 	mov rdi , 0; return

	syscall