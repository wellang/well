section .data
	 x: dw 1
	 y: dw 1
section .text

test2:

	mov rax, 60
	mov rdi, 0
	syscall
test1:

	mov rax, 60
	mov rdi, 0
	syscall


global main

main:
	
 extern printf

; 	move~ x, rdi
 	mov rdi, x; 	move~ y, rsi
 	mov rsi, y
 cmp rdi, rsi


 jnz test1


 jmp test2


	mov rax, 60
	mov rdi, 0
	syscall
