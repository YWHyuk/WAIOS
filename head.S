#define SWAPPER_MM_MMUFLAGS	0x711
#define DEVICE_MM_MMUFLAGS	0x701

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

	/* Create init page table */
	adrp	x0, init_pg_dir
	ldr	x1, =_text
	ldr	x2, =_end
	mov	x3, #SWAPPER_MM_MMUFLAGS
	adrp	x4, _text
	bl	map_memory

	/* Create identity page table */
	adrp	x0, idmap_pg_dir
	adrp	x1, _text
	adrp	x2, _end
	mov	x3, #SWAPPER_MM_MMUFLAGS
	adrp	x4, _text
	bl	map_memory

	/* identity mapping 1GB area for uart */
	adrp	x0, idmap_pg_dir
	add	x0, x0, #0x1000
	mov	x1, #DEVICE_MM_MMUFLAGS
	str	x1, [x0]

	/* enable mmu */
	bl	cpu_setup
	bl	enable_mmu

	ldr	x8, =start_kernel
	br	x8
