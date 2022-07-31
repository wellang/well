section .data
; 	string~ text = 'hello world'
 
	 text : db 'hello world', 10
	 text_length: equ $- text
section .text

%macro print 2
; 	move~ 1, rax
 	mov rax, 1; 	move~ 1, rdi
 	mov rdi, 1; 	move~ %%1, rsi
 	mov rsi, %1; 	move~ %%2, rdx
 	mov rdx, %2; 	syscall

	syscall
%endmacro


global _start

_start:
	
 print text, text_length


	mov rax, 60
	mov rdi, 0
	syscall
