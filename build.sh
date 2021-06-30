gcc -E -x c vmlinux.lds.S | grep -v '^#' > vmlinux.lds
gcc -c head.S uart.c main.c -fno-stack-protector
ld -T vmlinux.lds head.o uart.o main.o -o vmlinux
objcopy -O binary vmlinux Image
