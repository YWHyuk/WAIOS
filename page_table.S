#include "page_table.h"

.global cpu_setup
.global enable_mmu

.section ".text", "ax"
cpu_setup:
	mov	x1, #3 << 20
	msr	cpacr_el1, x1
	tlbi 	vmalle1
	dsb	nsh

	ldr 	x1,	=MAIR(0x00, MT_DEVICE_nGnRnE) | \
			 MAIR(0x04, MT_DEVICE_nGnRE) | \
			 MAIR(0x0c, MT_DEVICE_GRE) | \
			 MAIR(0x44, MT_NORMAL_NC) | \
			 MAIR(0xff, MT_NORMAL) | \
			 MAIR(0xbb, MT_NORMAL_WT)
	msr	mair_el1, x1

	ldr	x1, =TCR_TxSZ(VA_BITS) | TCR_CACHE_FLAGS | TCR_SMP_FLAGS | TCR_TG_FLAGS
	msr	tcr_el1, x1
	ret

enable_mmu:
	adrp	x1, init_pg_dir
	adrp    x2, idmap_pg_dir
	msr	ttbr0_el1, x2
	msr	ttbr1_el1, x1
	isb

	mrs 	x0, sctlr_el1
	orr 	x0, x0, #(0x1 << 2) 	// The C bit (data cache).
	orr 	x0, x0, #(0x1 << 12) 	// The I bit (instruction cache).
	orr 	x0, x0, #0x1 		// The M bit (MMU).
	msr 	sctlr_el1, x0
	isb
	/*
	* Invalidate the local I-cache so that any instructions fetched
	* speculatively from the PoC are discarded, since they may have
	* been dynamically patched at the PoU.
	*/
	ic	iallu
	dsb	nsh
	isb
	ret
