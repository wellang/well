section .data
;           string~ test = 'test'
 
	 test : db 'test'
	 tl: equ $- test
section .text



global main

main:
	;            move~ 1, rbp
 	mov rbp, 1;            move~ 1, rsp
 	mov rsp, 1;            move~ 5, r8
 	mov r8, 5;            move~ 4, r9
 	mov r9, 4
	cmp rbp, rsp
	je main._1rbprsp_eq
	jne main._1_fin
	._1rbprsp_eq:;                    move~ 1, rax
 	mov rax, 1;                    move~ 1, rdi
 	mov rdi, 1;                    move~ test, rsi
 	mov rsi, test;                    move~ tl, rdx
 	mov rdx, tl;                    syscall

	syscall
	jmp main._1_fin
	._1_fin:
	cmp r8, r9
	jne main._2r8r9_neq
	je main._2_fin
	._2r8r9_neq:;                     move~ 1, rax
 	mov rax, 1; 	                move~ 1, rdi
 	mov rdi, 1; 	                move~ test, rsi
 	mov rsi, test; 	                move~ tl, rdx
 	mov rdx, tl; 	                syscall

	syscall
	jmp main._2_fin
	._2_fin:
	cmp r8, r9
	jg main._3r8r9_gre
	jng main._3_fin
	._3r8r9_gre:;                     move~ 1, rax
 	mov rax, 1; 	                move~ 1, rdi
 	mov rdi, 1; 	                move~ test, rsi
 	mov rsi, test; 	                move~ tl, rdx
 	mov rdx, tl; 	                syscall

	syscall
	jmp main._3_fin
	._3_fin:
	cmp r9, r8
	jl main._4r9r8_les
	jnl main._4_fin
	._4r9r8_les:;                     move~ 1, rax
 	mov rax, 1;                     move~ 1, rdi
 	mov rdi, 1;                     move~ test, rsi
 	mov rsi, test;                     move~ tl, rdx
 	mov rdx, tl;                     syscall

	syscall
	jmp main._4_fin
	._4_fin:
	jmp main.3884if_test
	jmp main.3884if_testfin
	.3884if_test:;               move~ 1, eax
 	mov eax, 1;               move~ 2, ebx
 	mov ebx, 2
	cmp eax, ebx
	jne main._10000eaxebx_neq
	je main._10000_fin
	._10000eaxebx_neq:;                     move~ 1, rax
 	mov rax, 1;                     move~ 1, rdi
 	mov rdi, 1;                     move~ test, rsi
 	mov rsi, test;                     move~ tl, rdx
 	mov rdx, tl;                     syscall

	syscall
	jmp main._10000_fin
	._10000_fin:
	.3884if_testfin:

	mov rax, 60
	mov rdi,  0

	syscall