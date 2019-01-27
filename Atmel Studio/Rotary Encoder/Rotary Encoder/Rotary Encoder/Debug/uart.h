/*
 * uart.h
 *
 * Created: 28-12-2018 11:16:14
 *  Author: Chirag
 */ 


#ifndef UART_H_
#define UART_H_

void UART_putchar(unsigned char data);
void UART_putstring(unsigned char *txt);
unsigned char UART_getchar(void);
void UART_init(unsigned int ubrr);

#endif /* UART_H_ */