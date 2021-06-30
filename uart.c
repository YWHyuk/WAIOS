#include "uart.h"

void init_uart()
{
	uint8_t *reg8;
	uint16_t *reg16;
	uint32_t ibrd, fbrd;

	/* setting baudrate */
	reg16 = (uint16_t*)UARTIBRD_ADDR;
	reg8 = (uint8_t*)UARTFBRD_ADDR;
	ibrd = UARTCLK / (UART_BAUDRATE<<4);
	fbrd = (ibrd << 6) - ((UARTCLK / UART_BAUDRATE) << 2);
	fbrd = ((fbrd << 1) + 1) >> 1;

	*reg16 = ibrd;
	*reg8 = fbrd;

	/* setting line control */
	reg8 = (uint8_t*)UARTLCR_H_ADDR;
	*reg8 = UARTLCR_PEN | UARTLCR_EPS | UARTLCR_WLEN;

	/* interrupt fifo level skip*/

	/* mask all interrupt */
	reg16 = (uint16_t*)UARTMIS_ADDR;
	*reg16 = 0x7FF;

	/* DMA control skip*/

	/* setting control */
	reg16 = (uint16_t*)UARTCR_ADDR;
	*reg16 = UARTCR_RXE | UARTCR_TXE | UARTCR_UARTEN;
}

static int transmit_possible()
{
	uint8_t *reg8 = (uint8_t*)UARTFR_ADDR;
	return !(*reg8 & UARTFR_TXFF);
}

static int receive_possible()
{
	uint8_t *reg8 = (uint8_t*)UARTFR_ADDR;
	return !(*reg8 & UARTFR_RXFE);
}

int putchar(int c)
{
	uint8_t *reg8 = (uint8_t*)UARTDR_ADDR;
	
	while(!transmit_possible());
	*reg8 = (uint8_t)(c & 0xFF);

	return c;
}

int getchar()
{
	uint8_t *reg8 = (uint8_t*)UARTDR_ADDR;

	while(!receive_possible());
	return (int)(*reg8);
}
