gcc -E -x c vmlinux.lds.S | grep -v '^#' > vmlinux.lds
gcc -c head.S uart.c main.c printk.c -fno-stack-protector -Wall -mgeneral-regs-only
ld -T vmlinux.lds head.o uart.o main.o printk.o -o vmlinux
objcopy -O binary vmlinux Image
