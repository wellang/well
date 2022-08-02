section .data
;     string~ text = 'hello world!'
 
	 text : db 'hello world!', 0
	 text_length: equ $- text

 jmp loop1


 jmp jmploop


 call loop

section .text

jmploop:

 jmp loop1


 jmp jmploop

loop:

 jmp loop1


 jmp jmploop



global main

main:
	;     move~ 1, rax
 	mov rax, 1;     move~ 1, rdi
 	mov rdi, 1;     move~ text, rsi
 	mov rsi, text;     move~ text_length, rdx
 	mov rdx, text_length;     syscall

	syscall
 call loop


	mov rax, 60
	mov rdi, 0
	syscall
