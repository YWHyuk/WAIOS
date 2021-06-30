#include "uart.h"

void start_kernel(){
	char buffer[] = "Hello world!\n";
	init_uart();

	for(int i=0; i<13;i++){
		putchar(buffer[i]);
	}
	while(1){
		putchar(getchar());
	}
}

