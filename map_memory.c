#include "map_memory.h"

static uint64_t early_entries(uint64_t vstart, uint64_t vend, uint64_t shift)
{
	return (vend >> shift) - (vstart >> shift) + 1;
}

static void populate_entries(uint64_t *tbl, uint64_t *rtbl, uint64_t sindex, uint64_t nr_entries,
                      uint64_t flags, uint64_t inc)
{
	for (uint64_t i = sindex; i < sindex + nr_entries; i++, rtbl += inc / sizeof(uint64_t))
		tbl[i] = (uint64_t)rtbl | flags;
}

void map_memory(uint64_t *tbl, uint64_t vstart, uint64_t vend,
				uint64_t flags, uint64_t phys)
{
	uint64_t *rtbl;
	uint64_t nr_entries;
	uint64_t index;

	rtbl = tbl + PTRS_PER_PAGE;

	nr_entries = early_entries(vstart, vend, PGDIR_SHIFT);
	index = (vstart >> PGDIR_SHIFT) & (PTRS_PER_PAGE - 1);

	populate_entries(tbl, rtbl, index, nr_entries, TYPE_TABLE, PAGE_SIZE);

	tbl = rtbl;
	rtbl += PTRS_PER_PAGE * nr_entries;

	nr_entries = early_entries(vstart, vend, PUD_SHIFT);
	index = (vstart >> PUD_SHIFT) & (PTRS_PER_PAGE - 1);

	populate_entries(tbl, rtbl, index, nr_entries, TYPE_TABLE, PAGE_SIZE);

	tbl = rtbl;
	rtbl += PTRS_PER_PAGE * nr_entries;

	nr_entries = early_entries(vstart, vend, PMD_SHIFT);
	index = (vstart >> PMD_SHIFT) & (PTRS_PER_PAGE - 1);

	rtbl = (uint64_t*)(phys & PMD_MASK);
	populate_entries(tbl, rtbl, index, nr_entries, flags, PMD_SIZE);
}
