#define F_CPU 16000000

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "Serial.h"

/*
-Serial baud rate:9600
-Sends character 'K' every second
-Echos all characters given serially 
*/

unsigned char data; //to store received data from UDR

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

ISR(USART_RX_vect) 		// ISR for receive complete interrupt
{
	data = UDR0; 				//making copy of data from UDR1 in 'data' variable
	UDR0 = data; 				//echo data back to PC
}