	.section __TEXT,__text
	.global _on_ready
	.p2align 2
_on_ready:
	ldp x29, x30, [sp, #0]
	add sp, sp, #16
	ret
	.section __TEXT,__text
	.global _on_message
	.p2align 2
_on_message:
	ldp x29, x30, [sp, #0]
	add sp, sp, #16
	ret
	.section __TEXT,__text
	.global _main
	.p2align 2
_main:
	sub sp, sp, #16
	stp x29, x30, [sp, #0]
	add x29, sp, #0
	adrp x0,wl_str.BOT_TOKEN@PAGE
	add x0, x0, wl_str.BOT_TOKEN@PAGEOFF
	bl _discord_init
	str x0, [sp, #8]
	ldr x0, [sp, #8]
	adrp x1,wl_int_DISCORD_GATEWAY_MESSAGE_CONTENT@PAGE
	add x1, x1, wl_int_DISCORD_GATEWAY_MESSAGE_CONTENT@PAGEOFF
	bl _discord_add_intents
	adrp x0,wl_str.test@PAGE
	add x0, x0, wl_str.test@PAGEOFF
	bl _printf
	mov x0, #0
	ldp x29, x30, [sp, #0]
	add sp, sp, #16
	ret
wl_str.BOT_TOKEN:
	.asciz "TOKEN"
wl_str.test:
	.asciz "DO NOT REDEEM!\n"
