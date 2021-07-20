#include "uart.h"
#include "printk.h"

void start_kernel()
{
	init_uart();

	printk("[%s] %s %d", __func__, "Hello world!", 1);
	while(1);
}

