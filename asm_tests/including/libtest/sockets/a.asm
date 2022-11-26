section .data
section .bss
%macro move 2

	mov %2, %1

%endmacro
%macro MOVE 2

	mov %2, %1

%endmacro
%macro movess 2

	movss %2, %1

%endmacro
%macro MOVESS 2

	movess %2, $1

%endmacro
%macro jump 1

	jmp %1

%endmacro
%macro JUMP 1

	jmp %1

%endmacro
%macro pop 1

	pop %1

%endmacro
%macro POP 1

	pop %1

%endmacro
%macro add 2

	add %2, %1

%endmacro
%macro ADD 2

	add %2, %1

%endmacro
%macro sub 2

	sub %2, %1

%endmacro
%macro SUB 2

	sub %2, %1

%endmacro
%macro xor 2

	xor %2, %1

%endmacro
%macro XOR 2

	xor %2, %1

%endmacro
%macro aaa 0

	aaa

%endmacro
%macro AAA 0

	aaa

%endmacro
%macro aas 0

	aas

%endmacro
%macro AAS 0

	aas

%endmacro
%macro aad 1

	aad %1

%endmacro
%macro AAD 1

	aad %1

%endmacro
%macro aam 1

	aam %1

%endmacro
%macro AAM 1

	aam %1

%endmacro
%macro adc 2

	adc %2, %1 

%endmacro
%macro ADC 2

	adc %2, %1

%endmacro
%macro addpd 2

	addpd %2, %1

%endmacro
%macro ADDPD 2

	addpd %2, %1

%endmacro
%macro addps 2

	addps %2, %1

%endmacro
%macro ADDPS 2

	addps %2, %1

%endmacro
%macro addsd 2

	addsd %2, %1

%endmacro
%macro ADDSD 2

	addsd %2, %1

%endmacro
%macro addss 2

	addss %2, %1

%endmacro
%macro ADDSS 2

	addss %2, %1

%endmacro
%macro and 2

	and %2, %1

%endmacro
%macro AND 2

	and %2, %1

%endmacro
%macro andnpd 2

	andnpd %2, %1

%endmacro
%macro ANDNPD 2

	andnpd %2, %1

%endmacro
%macro andnps 2

	andnps %2, %1

%endmacro
%macro ANDNPS 2

	andnps %2, %1

%endmacro
%macro andpd 2

	andpd %2, %1

%endmacro
%macro ANDPD 2

	andpd %2, %1

%endmacro
%macro andps 2

	andps %2, %1

%endmacro
%macro ANDPS 2

	andps %2, %1

%endmacro
%macro arpl 2

	arpl %2, %1

%endmacro
%macro ARPL 2

	arpl %2, %1

%endmacro
%macro bscanl 2

	bsf %2, %1

%endmacro
%macro BSCANL 2

	bsf %2, %1

%endmacro
%macro bscanm 2

	bsr %2, %1

%endmacro
%macro BSCANM 2

	bsr %2, %1

%endmacro
%macro bswap 1

	bswap %1

%endmacro
%macro BSWAP 1

	bswap %1

%endmacro
%macro bt 2

	bt %2, %1

%endmacro
%macro BT 2

	bt %2, %1

%endmacro
%macro btc 2

	btc %2, %1

%endmacro
%macro BTC 2

	btc %2, %1

%endmacro
%macro btr 2

	btr %2, %1

%endmacro
%macro BTR 2

	btr %2, %1

%endmacro
%macro bts 2

	bts %2, %1

%endmacro
%macro BTS 2

	bts %2, %1

%endmacro
%macro cbw 0

	cbw

%endmacro
%macro CBW 0

	cbw

%endmacro
%macro cwde 0

	cwde

%endmacro
%macro CWDE 0

	cwde

%endmacro
%macro cwd 0

	cwd

%endmacro
%macro CWD 0

	cwd

%endmacro
%macro cdq 0

	cdq

%endmacro
%macro CDQ 0

	cdq

%endmacro
%macro clc 0

	clc

%endmacro
%macro CLC 0

	clc

%endmacro
%macro cld 0

	cld

%endmacro
%macro CLD 0

	cld

%endmacro
%macro clts 0

	clts

%endmacro
%macro CLTS 0

	clts

%endmacro
%macro clflush 1

	clflush %1

%endmacro
%macro CLFLUSH 1

	clflush %1

%endmacro
%macro cmc 0

	cmc

%endmacro
%macro CMC 0

	cmc

%endmacro
%macro cmove 2

	cmov %2, %1

%endmacro
%macro CMOVE 2

	cmov %2, %1

%endmacro
%macro cmovecc 2

	cmovcc %2, %1

%endmacro
%macro CMOVECC 2

	cmovcc %2, %1

%endmacro
%macro cpuid 0

	cpuid

%endmacro
%macro CPUID 0

	cpuid

%endmacro
%macro cvtdq2pd 2

	cvtdq2pd %2, %1

%endmacro
%macro CVTDQ2PD 2

	cvdq2pd %2, %1

%endmacro
%macro cvtdq2ps 2

	cvtdq2ps %2, %1

%endmacro
%macro CVTDQ2PS 2

	cvtdq2ps %2, %1

%endmacro
%macro cvtp2dq 2

	cvtp2dq %2, %1

%endmacro
%macro CVTP2DQ 2

	cvtp2dq %2, %1

%endmacro
%macro cvtpd2pi 2

	cvtpd2pi %2, %1

%endmacro
%macro CVTPD2PI 2

	cvtpd2pi %2, %1

%endmacro
%macro return 1

	move  60, rax
	move  %1, rdi; 	syscall	

	syscall
%endmacro

section .text



global main

main:
	
	move  6, r8
	jmp main_1sock_init_
	jmp main_1sock_init_fin
	main_1sock_init_:
	cmp r8, 0x00
	je main_9_2000r80x00_eq
	jne main_9_2000_fin
	main_9_2000r80x00_eq:;                     move~ 0, r8
 	mov r8, 0
	jmp main_9_2000_fin
	main_9_2000_fin:
	cmp rsi, 0x00
	jne main_12_2001rsi0x00_neq
	je main_12_2001_fin
	main_12_2001rsi0x00_neq:
	xor rsi, rsi

	jmp main_12_2001_fin
	main_12_2001_fin:
	cmp rdi, 0x00
	jne main_15_2002rdi0x00_neq
	je main_15_2002_fin
	main_15_2002rdi0x00_neq:
	xor rdi, rdi

	jmp main_15_2002_fin
	main_15_2002_fin:;             move~ r8, rdx
 	mov rdx, r8;             move~ 1, rsi
 	mov rsi, 1;             move~ 2, rdi
 	mov rdi, 2;             move~ 41, rax
 	mov rax, 41;             syscall

	syscall;             move~ rax, r9
 	mov r9, rax
	xor r8, r8

	main_1sock_init_fin:

	jmp main_2sock_bind_
	jmp main_2sock_bind_fin
	main_2sock_bind_:
	cmp r9, 0x00
	je main_35_2000r90x00_eq
	jne main_35_2000_fin
	main_35_2000r90x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main_35_2000_fin
	main_35_2000_fin:
	cmp r10, 0x00
	je main_38_2001r100x00_eq
	jne main_38_2001_fin
	main_38_2001r100x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main_38_2001_fin
	main_38_2001_fin:
	cmp r11, 0x00
	je main_41_2002r110x00_eq
	jne main_41_2002_fin
	main_41_2002r110x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main_41_2002_fin
	main_41_2002_fin:;            move~ r9, rdi
 	mov rdi, r9;            move~ r10, rsi
 	mov rsi, r10;            move~ r11, rdx
 	mov rdx, r11;            move~ 49, rax
 	mov rax, 49;            syscall

	syscall;            move~ rdi, r9
 	mov r9, rdi
	main_2sock_bind_fin:

	jmp main_3sock_listen_
	jmp main_3sock_listen_fin
	main_3sock_listen_:
	cmp r9, 0x00
	je main_58_2000r90x00_eq
	jne main_58_2000_fin
	main_58_2000r90x00_eq:
	mov rax, 60
	mov rdi,  1

	syscall
	jmp main_58_2000_fin
	main_58_2000_fin:;            move~ r9, rdi
 	mov rdi, r9;            move~ 50, rsi
 	mov rsi, 50;            move~ 50, rax
 	mov rax, 50;            syscall

	syscall
	main_3sock_listen_fin:

	return  0
