/*
Encoder connections

CLK : PD3
DT  : PD7
SW  : PD2
+	: 5V
GND : GND

No other connections (like pull-up resistors) are required
*/

#define F_CPU 16000000
#define UART_BAUD 9600				/* serial transmission speed */
#define UART_CONST F_CPU/16/UART_BAUD-1

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "Serial.h"

volatile int count = 0;
volatile int previous_count = 0;

volatile int enable_counting = 1;		//to avoid bouncing

//If button is pressed (Falling edge)
//INT0 interrupt (PD2)
ISR(INT0_vect)
{
	UDR0 = 'b';
}

//If a falling edge is detected 
//INT1 interrupt (PD3)
ISR(INT1_vect)
{
	if(enable_counting == 1)	
	{
		enable_counting = 0;	//to avoid bouncing, don't count more until this count is registered
		
		if(!bit_is_clear(PIND, PD7))
		{
			count++;
			UDR0 = '+';
		}
		else
		{
			count--;
			UDR0 = '-';
		}
	}
}

int main(void)
{
	cli();								//Disable all interrupts
	
	/* set PD2 and PD3 as input */
	DDRD &=~ (1 << 7);					//DT
	DDRD &=~ (1 << 3);					//CLK
	//PORTD |= (1 << 3)|(1 << 7);		/* PD2 and PD3 pull-up enabled   */
	
	EIMSK |= (1<<INT1);					// enable INT1
	EIMSK |= (1<<INT0);					// enable INT0
	EICRA |= (1<<ISC11)|(1<<ISC10);		//INT1 - rising edge */
	EICRA |= (1<<ISC01);				//INT1 - falling edge */

	uart0_init(); //Initialize UART0 for serial communication
	
	sei();								//enable interrupts 
	
	while(1)
	{
		//If count change is detected. ie the encoder is turned.
		if(count != previous_count)
		{
			UDR0 = '.';
			
			enable_counting = 1;			
			previous_count = count;
		}
	}
	return 0;
}
