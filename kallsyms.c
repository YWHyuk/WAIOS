#include <stddef.h>
#include <stdint.h>
#include "kallsyms.h"

extern unsigned int kallsym_table_cnt __attribute((weak));
extern struct symbol kallsym_table[] __attribute((weak));

const struct symbol* addr_to_symbol(uint64_t addr)
{
        unsigned int start, end, middle;
        
        start = 0;
        end = kallsym_table_cnt;
        
        while (1) {
                middle = (start + end) / 2; 
                if (start == middle)
                        break;

                if (kallsym_table[middle].addr < addr)
                        start = middle; 
                else if (kallsym_table[middle].addr > addr)
                        end = middle; 
                else
                        return kallsym_table+middle;
        }

        if (kallsym_table[middle].addr > addr)
                return NULL;
        else
                return kallsym_table+middle;

}
