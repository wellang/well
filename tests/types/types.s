	.section __TEXT,__text
	.global _main
	.p2align 2
_main:
wl_str.str.0:
	.asciz "STRING"

	.global wl_ch_ch0
wl_ch_ch0:
	.byte 67

	.global wl_int_i0
	.p2align 2,0x0
wl_int_i0:
	.long 0x5C6
 
