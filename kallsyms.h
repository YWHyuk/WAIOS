#ifndef __KALLSYMS
#define __KALLSYMS

struct symbol {
        uint64_t addr;
        char* sym;
};

const struct symbol* addr_to_symbol(uint64_t addr);

#endif
