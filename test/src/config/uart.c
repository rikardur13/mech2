/*
 * uart.c
 *
 * Created: 21.1.2017 14:03:21
 *  Author: nanna
 */ 

#include "uart.h"

//#define CONSOLE_UART               UART
//#define CONSOLE_UART_ID            ID_UART
void uart_init(void)
{
	/* Configure peripheral clock UART. */
	PMC->PMC_PCER0 = (1 << ID_UART);
	/* Enable receiver and transmitter */
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
	/* Turn parity mode off */
	UART->UART_MR = UART_MR_PAR_NO;	
	/* Baud rate generator register */
	UART->UART_BRGR = CLOCKDIVISION;
	
	/* FUTURE WORK */
	// Transmission interrupt enable to minimize calculation downtime
	//UART->UART_IER = UART_IER_ENDTX;
	// viljum 2 bit stop bits 8 bit data, asynchronous mode, parity mode off,
}

void uart_transfer(uint8_t transmit)
{
	while (!(UART->UART_SR & UART_SR_TXRDY));
	UART->UART_THR = transmit;
}
//Send Integers over to terminal
void uart_print_int(uint32_t data)
{
	uint32_t div = 1000000000;		// Divider to divide data with
	uint8_t start = 0;
	uint8_t cnt = 10;
	for (int i = 1; i <= cnt; i++)
	{
		uint8_t send = data / div + 48; // calculate the Ascii for each number
		if(send != 48 || start == 1 || i == cnt)
		{
			//Wait until hardware is ready to send data, UDRE0 = Data register empty
			uart_transfer(send);
			start = 1;
		}
		data %= div;
		div /= 10;
	}
	uart_new_line();
}
void uart_new_line(void)
{
	uart_transfer(10);
}

void uart_print_string(char * data)
{
	int i = 0;
	// loop which print strings till null is reached or more than 20 characters (for safety)
	while(data[i] != 0 || i > 20)
		uart_transfer(data[i++]);
	uart_transfer(32); // space

}