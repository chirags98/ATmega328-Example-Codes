/*
 * Serial.c
 *
 * Created: 18-03-2018 11:30:10 AM
 *  Author: Chirag
 */ 

#include<avr/io.h>

//Function To Initialize UART0
// desired baud rate:9600
// actual baud rate:9600 (error 0.2%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	UBRR0L = 0x67; //set baud rate lo //UBRR0 = 103
	UBRR0H = 0x00; //set baud rate hi
	UCSR0B = 0x98;
}
