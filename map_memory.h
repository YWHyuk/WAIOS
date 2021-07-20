#ifndef __MAP_MEMORY
#define __MAP_MEMORY
#include "page_table.h"
#include <stdint.h>

#define CONFIG_PGTABLE_LEVELS   4
#define CONFIG_ARM64_PAGE_SHIFT 12

#define SWAPPER_PGTABLE_LEVELS  3

#define PAGE_SHIFT      CONFIG_ARM64_PAGE_SHIFT
#define PAGE_SIZE       (1UL << PAGE_SHIFT)

#define PGDIR_SHIFT     39
#define PUD_SHIFT       30
#define PMD_SHIFT       21

#define PGDIR_SIZE      (1UL << PGDIR_SHIFT)
#define PUD_SIZE        (1UL << PUD_SHIFT)
#define PMD_SIZE        (1UL << PMD_SHIFT)

#define PGDIR_MASK      (~(PGDIR_SIZE-1))
#define PUD_MASK        (~(PUD_SIZE-1))
#define PMD_MASK        (~(PMD_SIZE-1))

#define PTRS_PER_PAGE   (PAGE_SIZE >> 3)

#define TYPE_TABLE      (3 << 0)
#define TYPE_SECT       (1 << 0)

#define PTE_ATTRINDX(t) (t << 2)
#define PMD_SECT_S      (3 << 8)
#define PMD_SECT_AF     (1 << 10)

#define SWAPPER_PMD_FLAGS       (PMD_TYPE_SECT | PMD_SECT_AF | PMD_SECT_S)
#define SWAPPER_MM_MMUFLAGS     (PTE_ATTRINDX(MT_NORMAL) | SWAPPER_PTE_FLAGS)

void map_memory(uint64_t *tbl, uint64_t vstart, uint64_t vend,
				uint64_t flags, uint64_t phys);
#endif
