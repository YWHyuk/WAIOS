#include "uart.h"
#include "printk.h"

void start_kernel()
{
	char *buffer = "Hello world!";
	init_uart();

	printk("%s %d\n", buffer, 1);
	while(1);
}

