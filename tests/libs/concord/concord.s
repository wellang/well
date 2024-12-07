	.extern discord_init
	.extern discord_add_intents
	.extern discord_set_on_ready
	.extern discord_set_on_message_create
	.extern discord_run
	.extern discord_create_message
	.extern log_log
	.extern log_info

	.global wl_int_DISCORD_GATEWAY_MESSAGE_CONTENT
	.p2align 2,0x0
wl_int_DISCORD_GATEWAY_MESSAGE_CONTENT:
	.long 0x0
