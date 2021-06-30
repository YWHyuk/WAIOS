gcc -E -x c vmlinux.lds.S | grep -v '^#' > vmlinux.lds
gcc -c head.S page_table.S uart.c main.c printk.c map_memory.c -fno-stack-protector -Wall -mgeneral-regs-only -g
ld -T vmlinux.lds head.o page_table.o uart.o main.o printk.o map_memory.o -o vmlinux
objcopy -O binary vmlinux Image
