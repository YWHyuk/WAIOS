#ifndef __PAGE_TABLE_H
#define __PAGE_TABLE_H

#define VA_BITS		48
#define MAIR(attr, mt)	((attr) << ((mt) * 8))

#define UL(x)		(x)

/* MAIR_ELx memory attributes (used by Linux) */
#define MT_DEVICE_nGnRnE	0
#define MT_DEVICE_nGnRE		1
#define MT_DEVICE_GRE		2
#define MT_NORMAL_NC		3
#define MT_NORMAL		4
#define MT_NORMAL_WT		5

/*
 * TCR flags.
 */
#define TCR_T0SZ_OFFSET         0
#define TCR_T1SZ_OFFSET         16
#define TCR_T0SZ(x)             ((UL(64) - (x)) << TCR_T0SZ_OFFSET)
#define TCR_T1SZ(x)             ((UL(64) - (x)) << TCR_T1SZ_OFFSET)
#define TCR_TxSZ(x)             (TCR_T0SZ(x) | TCR_T1SZ(x))

#define TCR_IRGN0_SHIFT         8
#define TCR_IRGN1_SHIFT         24

#define TCR_IRGN0_WBWA          (UL(1) << TCR_IRGN0_SHIFT)
#define TCR_IRGN1_WBWA          (UL(1) << TCR_IRGN1_SHIFT)

#define TCR_IRGN_WBWA           (TCR_IRGN0_WBWA | TCR_IRGN1_WBWA)

#define TCR_ORGN0_SHIFT         10
#define TCR_ORGN1_SHIFT         26

#define TCR_ORGN0_WBWA          (UL(1) << TCR_ORGN0_SHIFT)
#define TCR_ORGN1_WBWA          (UL(1) << TCR_ORGN1_SHIFT)

#define TCR_ORGN_WBWA           (TCR_ORGN0_WBWA | TCR_ORGN1_WBWA)

#define TCR_CACHE_FLAGS         TCR_IRGN_WBWA | TCR_ORGN_WBWA

#define TCR_TG0_SHIFT           14
#define TCR_TG0_4K              (UL(0) << TCR_TG0_SHIFT)

#define TCR_TG1_SHIFT           30
#define TCR_TG1_4K              (UL(2) << TCR_TG1_SHIFT)

#define TCR_TG_FLAGS            TCR_TG0_4K | TCR_TG1_4K

#define TCR_SH0_SHIFT           12
#define TCR_SH0_INNER           (UL(3) << TCR_SH0_SHIFT)

#define TCR_SH1_SHIFT           28
#define TCR_SH1_INNER           (UL(3) << TCR_SH1_SHIFT)

#define TCR_SHARED              (TCR_SH0_INNER | TCR_SH1_INNER)
#define TCR_SMP_FLAGS           TCR_SHARED

#endif
