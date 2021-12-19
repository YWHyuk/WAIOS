#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define KSYM_NAME_LEN           128

struct symbol {
        uint64_t addr;
        char *sym;
};

static struct symbol *table;
static unsigned int table_size, table_cnt;

static int read_symbol(FILE *in, struct symbol *s)
{
        char sym[500], stype;
        int rc;

        rc = fscanf(in, "%lx %c %499s\n", &s->addr, &stype, sym);
        if (rc != 3) {
                if (rc != EOF && fgets(sym, 500, in) == NULL)
                        fprintf(stderr, "Read error or end of file.\n");
                return -1;
        }
        if (strlen(sym) >= KSYM_NAME_LEN) {
                fprintf(stderr, "Symbol %s too long for kallsyms (%zu >= %d).\n"
                                "Please increase KSYM_NAME_LEN both in kernel and kallsyms.c\n",
                        sym, strlen(sym), KSYM_NAME_LEN);
                return -1;
        }
        if (stype != 'T' && stype != 't')
                return -1;

        s->sym = malloc(strlen(sym)+1);
        if (!s->sym) {
                fprintf(stderr, "kallsyms failure: "
                        "unable to allocate required amount of memory\n");
                exit(EXIT_FAILURE);
        }
        strcpy((char *)s->sym, sym);
        return 0;
}

static void read_map(FILE *in)
{
        while (!feof(in)) {
                if (table_cnt >= table_size) {
                        table_size += 10000;
                        table = realloc(table, sizeof(*table) * table_size);
                        if (!table) {
                                fprintf(stderr, "out of memory\n");
                                exit (1);
                        }
                }
                if (read_symbol(in, &table[table_cnt]) == 0) {
                        table_cnt++;
                }
        }
}

static int compare_symbols(const void *a, const void *b)
{
        const struct symbol *sa;
        const struct symbol *sb;
        int wa, wb;

        sa = a;
        sb = b;

        /* sort by address first */
        if (sa->addr > sb->addr)
                return 1;
        if (sa->addr <= sb->addr)
                return -1;
}

static void write_src(void)
{
        printf("#include <stdint.h>\n");
        printf("struct symbol {\n\tuint64_t addr;\n\tchar *sym;\n};\n");
        printf("unsigned int kallsym_table_cnt = %d;\n", table_cnt);
        printf("struct symbol kallsym_table[%d] = {\n", table_cnt);
        for (int i=0; i<table_cnt; i++) {
               printf("\t{%p,\"%s\"},\n", (void*)table[i].addr, table[i].sym); 
        }
        printf("};\n");
}

int main()
{
        read_map(stdin);
        qsort(table, table_cnt, sizeof(struct symbol), compare_symbols);
        write_src();

        return 0;
}
