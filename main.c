#include "uart.h"
#include "printk.h"
#include "dump_stack.h"

void b()
{
        dump_stack();
        while(1);
}
void a()
{
        b();
}
void start_kernel()
{
	init_uart();

	printk("[%s] %s %d\n", __func__, "Hello world!", 1);
        a();
}

