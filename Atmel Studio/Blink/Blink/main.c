/*
 * Blink.c
 *
 * Created: 14-03-2018 04:45:38 PM
 * Author : Chirag
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRD = DDRD | 0x80;		//Setting PORTD 7 as output
	PORTD = PORTD & 0x80;	//Setting PORTD 7 logic low to turnoff led

	while (1)
	{
		PORTD = PORTD ^ 0x80;
		_delay_ms(2000);
	}
}

