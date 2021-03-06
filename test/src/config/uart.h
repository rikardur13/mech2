/*
 * uart.h
 *
 * Created: 21.1.2017 14:16:25
 *  Author: nanna
 */ 
 

#include <asf.h>

#ifndef UART_H_
#define UART_H_

#define ATSAM3X8E_MCK 84000000
#define BAUDRATE 115200
#define CLOCKDIVISION ATSAM3X8E_MCK/(BAUDRATE*16)
#define TXBUFFERSIZE 1024
#define RXBUFFERSIZE 1024

volatile uint8_t TxString[TXBUFFERSIZE];
volatile uint16_t TxStringHead;
volatile uint16_t TxStringTail;

volatile uint8_t RxString[RXBUFFERSIZE];
volatile uint16_t RxStringHead;
volatile uint16_t RxStringTail;

volatile uint8_t RxFlag;

void uart_init(void);
void uart_tx_interrupt_init(void);
void uart_interrupt_transfer(char* str);
void uart_rx_interrupt_init(void);
void uart_rx_read_buffer(void);
void uart_transfer(uint8_t transmit);
void uart_print_int(uint32_t data);
void uart_new_line(void);
void uart_print_string(char * data);

#endif /* UART_H_ */