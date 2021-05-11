gcc -E -x c vmlinux.lds.S | grep -v '^#' > vmlinux.lds
gcc -c head.S
ld -T vmlinux.lds head.o -o vmlinux
objcopy -O binary vmlinux Image
