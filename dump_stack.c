#include <stdint.h>
#include "kallsyms.h"
#include "printk.h"

void dump_stack()
{
        uint64_t *frame;
        uint64_t pc;

        frame = __builtin_frame_address(0);
        
        printk("*** Dump Stack ***\n");
        printk("Call trace:\n");
        for ( ;frame; frame=(uint64_t*)*frame) {
                pc = frame[1];
                const struct symbol *s = addr_to_symbol(pc);
                printk(" [<%0x%p>] %s+0x%p\n", pc, s->sym?: "?", pc - s->addr);
        }
}
