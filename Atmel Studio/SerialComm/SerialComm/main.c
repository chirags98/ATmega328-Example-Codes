#define F_CPU 16000000

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "Serial.h"

//Function To Initialize all The Devices
void init_devices()
{
 cli(); //Clears the global interrupts
 uart0_init(); //Initialize UART0 for serial communication
 sei();   //Enables the global interrupts
}

//Main Function
int main(void)
{
	init_devices();
	while(1)
	{
		UDR0 = 'K';
		_delay_ms(1000);
	}
}