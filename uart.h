#ifndef __UART
#define __UART
#include <stdint.h>

/* Reference device tree or qemu's virt.c */
#define UART_BASE_ADDR	0x09000000
#define UARTCLK		24000000

/* your choice */
#define UART_BAUDRATE 	1152000

#define UARTDR_ADDR	(UART_BASE_ADDR + 0x00)
#define UARTRSR_ADDR	(UART_BASE_ADDR + 0x04)
#define UARTECR_ADDR	(UART_BASE_ADDR + 0x04)
#define	UARTFR_ADDR	(UART_BASE_ADDR + 0x18)
#define UARTIBRD_ADDR	(UART_BASE_ADDR + 0x24)
#define UARTFBRD_ADDR	(UART_BASE_ADDR + 0x28)
#define UARTLCR_H_ADDR	(UART_BASE_ADDR + 0x2C)
#define UARTCR_ADDR	(UART_BASE_ADDR + 0x30)
#define UARTIFLS_ADDR	(UART_BASE_ADDR + 0x34)
#define UARTIMSC_ADDR	(UART_BASE_ADDR + 0x38)
#define UARTRIS_ADDR	(UART_BASE_ADDR + 0x3C)
#define UARTMIS_ADDR	(UART_BASE_ADDR + 0x40)
#define UARTICR_ADDR	(UART_BASE_ADDR + 0x44)
#define UARTDMACR_ADDR	(UART_BASE_ADDR + 0x48)

#define UARTFR_RI	(0x01 << 8)
#define UARTFR_TXFE	(0x01 << 7)
#define UARTFR_RXFF	(0x01 << 6)
#define UARTFR_TXFF	(0x01 << 5)
#define UARTFR_RXFE	(0x01 << 4)
#define UARTFR_BUSY	(0x01 << 3)
#define UARTFR_DCD	(0x01 << 2)
#define UARTFR_DSR	(0x01 << 1)
#define UARTFR_CTS	(0x01 << 0)

#define UARTLCR_SPS	(0x01 << 7)
#define UARTLCR_WLEN	(0x03 << 5)
#define UARTLCR_FEN	(0x01 << 4)
#define UARTLCR_STP2	(0x01 << 3)
#define UARTLCR_EPS	(0x01 << 2)
#define UARTLCR_PEN	(0x01 << 1)
#define UARTLCR_BRK	(0x01 << 0)

#define UARTCR_CTSEN	(0x01 << 15)
#define UARTCR_RTSEN	(0x01 << 14)
#define UARTCR_OUT2	(0x01 << 13)
#define UARTCR_OUT1	(0x01 << 12)
#define UARTCR_RTS	(0x01 << 11)
#define UARTCR_DTR	(0x01 << 10)
#define UARTCR_RXE	(0x01 << 9)
#define UARTCR_TXE	(0x01 << 8)
#define UARTCR_LBE	(0x01 << 7)
#define UARTCR_SIRLP	(0x01 << 2)
#define UARTCR_SIREN	(0x01 << 1)
#define UARTCR_UARTEN	(0x01 << 0)

void init_uart();
int putchar(int c);
int getchar();

#endif
