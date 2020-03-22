/*
 * SPI.c
 *
 * Created: 15-10-2019 3.56.56 PM
 * Author : ADMIN
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include "SPI.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define master 1		//1 if master, 0 if slave

#define sbit(reg,bit)	reg |= (1<<bit)			// Macro defined for Setting a bit of any register.
#define cbit(reg,bit)	reg &= ~(1<<bit)		// Macro defined for Clearing a bit of any register.
#define read_bit(reg, bit)	reg & (1<<bit)		// Macro defined for reading a bit of any register.

int received_data = 0;

void port_config (void)
{
	lcd_port_config();
}

void init_devices (void)
{
	cli(); //Clears the global interrupts
	lcd_start();
	sei();   //Enables the global interrupts
}

int main(void)
{
	port_config();
	init_devices();
	
	if (master)
	{
		lcd_string2(1, 1, "SPI Test");
		spiInitMaster();
		_delay_ms(1000);	
	}
	else
	{
		lcd_string2(1, 1, "SPI Slave");
		spiInitSlave();
		_delay_ms(1000);
	}
		
    /* Replace with your application code */
    while (1) 
    {
		if (master)
		{
			for(uint8_t i = 0; i<10;i++)
			{
				#define cs1 2
				spiTransmit(i, cs1);
				lcd_string2(2, 1, "Sending ");
				lcd_print(2, 9, i, 2);
				_delay_ms(1000);
			}
		}
		else
		{
			//lcd_string2(1, 15, "1");
			received_data = spiReceive();
			//lcd_string2(1, 15, "2");
			lcd_string2(2, 1, "Received ");
			lcd_print(2, 10, received_data, 2);
		}			
    }
}

