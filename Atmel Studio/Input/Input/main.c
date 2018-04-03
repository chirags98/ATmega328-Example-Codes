/*
 * Input.c
 *
 * Created: 03-04-2018 10:15:40 PM
 * Author : Chirag
 */ 

/*
-A push button is connected to PB4 and ground. 
-When the button is pressed PB4 is grounded and the onboard LED on PB5 turns off.
-Otherwise the internal pullup maintains PB4 at a logic high level.
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//PORTB 4 is by default input
	PORTB = PORTB | 0x10;	//Activate the pull-up on PB4
	
	DDRB = DDRB | 0x20;		//Setting PORTB 5 as output
		
	while (1)
	{
		if (PINB & 0x10)
		{
			PORTB = PORTB | 0x20;	//LED is on
		}
		else
		{
			PORTB = ~(~PORTB | 0x20);	//LED is off
		}
			
		_delay_ms(50);
	}
}

