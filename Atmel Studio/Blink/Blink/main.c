/*
 * Blink.c
 *
 * Created: 14-03-2018 04:45:38 PM
 * Author : Chirag
 */ 

/*
Blinks the onboard LED connected to PB5 with a delay of one second.
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRB = DDRB | 0x20;		//Setting PORTB 5 as output

	while (1)
	{
		PORTB = PORTB ^ 0x20;	//Toggle output between high and low
		_delay_ms(1000);
	}
}

