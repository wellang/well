section .data
;           string~ test = 'test'
 
	 test: db 'test', 0
	.len: equ $- test
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
	
	move  1, rbp
	move  1, rsp
	move  5, r8
	move  4, r9
	cmp rbp, rsp
	je main_15_1rbprsp_eq
	jne main_15_1_fin
	main_15_1rbprsp_eq:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx;                    syscall

	syscall
	jmp main_15_1_fin
	main_15_1_fin:
	cmp r8, r9
	jne main_25_2r8r9_neq
	je main_25_2_fin
	main_25_2r8r9_neq:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx; 	                syscall

	syscall
	jmp main_25_2_fin
	main_25_2_fin:
	cmp r8, r9
	jg main_35_3r8r9_gre
	jng main_35_3_fin
	main_35_3r8r9_gre:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx; 	                syscall

	syscall
	jmp main_35_3_fin
	main_35_3_fin:
	cmp r9, r8
	jl main_45_4r9r8_les
	jnl main_45_4_fin
	main_45_4r9r8_les:
	move  1, rax
	move  1, rdi
	move  test, rsi
	move  test.len, rdx;                     syscall

	syscall
	jmp main_45_4_fin
	main_45_4_fin:
	jmp main_1if_test_
	jmp main_1if_test_fin
	main_1if_test_:;               move~ 1, eax
 	mov eax, 1;               move~ 2, ebx
 	mov ebx, 2
	cmp eax, ebx
	jne main_6_10000eaxebx_neq
	je main_6_10000_fin
	main_6_10000eaxebx_neq:;                     move~ 1, rax
 	mov rax, 1;                     move~ 1, rdi
 	mov rdi, 1;                     move~ test, rsi
 	mov rsi, test;                     move~ test.len, rdx
 	mov rdx, test.len;                     syscall

	syscall
	jmp main_6_10000_fin
	main_6_10000_fin:
	jmp main_1if_test_fin
	main_1if_test_fin:

	return  0
