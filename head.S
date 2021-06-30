.section ".head.text", "ax"
_head:
	b	text
	.long	0
	.quad	kernel_offset
	.quad	kernel_size
	.quad	kernel_flag
	.quad	0
	.quad	0
	.quad 	0
	.ascii	"ARM\x64"
	.long	0

.section ".text", "ax"
text:
	adrp	x1, stack_top
	mov	sp, x1
	b	start_kernel
