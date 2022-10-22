section .data

section .text



global main

main:
	
	jmp main._1sock_init_
	jmp main._1sock_init_fin
	._1sock_init_:
	cmp r8, 0x00
	je main._9_2000r80x00_eq
	jne main._9_2000_fin
	._9_2000r80x00_eq:;                     move~ 0, r8
 	mov r8, 0
	jmp main._9_2000_fin
	._9_2000_fin:
	cmp rsi, 0x00
	jne main._12_2001rsi0x00_neq
	je main._12_2001_fin
	._12_2001rsi0x00_neq:
	xor rsi, rsi

	jmp main._12_2001_fin
	._12_2001_fin:
	cmp rdi, 0x00
	jne main._15_2002rdi0x00_neq
	je main._15_2002_fin
	._15_2002rdi0x00_neq:
	xor rdi, rdi

	jmp main._15_2002_fin
	._15_2002_fin:;             move~ r8, rdx
 	mov rdx, r8;             move~ 1, rsi
 	mov rsi, 1;             move~ 2, rdi
 	mov rdi, 2;             move~ 41, rax
 	mov rax, 41;             syscall

	syscall;             move~ rax, r9
 	mov r9, rax
	xor r8, r8

	._1sock_init_fin:

	jmp main._2sock_bind_
	jmp main._2sock_bind_fin
	._2sock_bind_:
	cmp r9, 0x00
	je main._35_2000r90x00_eq
	jne main._35_2000_fin
	._35_2000r90x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main._35_2000_fin
	._35_2000_fin:
	cmp r10, 0x00
	je main._38_2001r100x00_eq
	jne main._38_2001_fin
	._38_2001r100x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main._38_2001_fin
	._38_2001_fin:
	cmp r11, 0x00
	je main._41_2002r110x00_eq
	jne main._41_2002_fin
	._41_2002r110x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main._41_2002_fin
	._41_2002_fin:;            move~ r9, rdi
 	mov rdi, r9;            move~ r10, rsi
 	mov rsi, r10;            move~ r11, rdx
 	mov rdx, r11;            move~ 49, rax
 	mov rax, 49;            syscall

	syscall;            move~ rdi, r9
 	mov r9, rdi
	._2sock_bind_fin:

	jmp main._3sock_listen_
	jmp main._3sock_listen_fin
	._3sock_listen_:
	cmp r9, 0x00
	je main._58_2000r90x00_eq
	jne main._58_2000_fin
	._58_2000r90x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main._58_2000_fin
	._58_2000_fin:;            move~ r9, rdi
 	mov rdi, r9;            move~ 50, rsi
 	mov rsi, 50;            move~ 50, rax
 	mov rax, 50;            syscall

	syscall
	._3sock_listen_fin:
