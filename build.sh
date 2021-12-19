gcc -E -x c vmlinux.lds.S | grep -v '^#' > vmlinux.lds
gcc -c head.S page_table.S uart.c main.c printk.c map_memory.c dump_stack.c kallsyms.c -fno-stack-protector -Wall -mgeneral-regs-only -g
ld -r -T vmlinux.lds head.o page_table.o uart.o main.o printk.o map_memory.o -o vmlinux
nm vmlinux | ./scripts/kallsyms > source.c
gcc -c source.c
ld -T vmlinux.lds head.o page_table.o uart.o main.o printk.o map_memory.o dump_stack.o kallsyms.o source.o -o vmlinux2
nm vmlinux2 | ./scripts/kallsyms > source.c
gcc -c source.c
ld -T vmlinux.lds head.o page_table.o uart.o main.o printk.o map_memory.o dump_stack.o kallsyms.o source.o -o vmlinux
objcopy -O binary vmlinux Image
