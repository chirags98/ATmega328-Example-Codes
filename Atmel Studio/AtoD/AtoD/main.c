/*
 * AtoD.c
 *
 * Created: 18-03-2018 12:02:16 AM
 * Author : Chirag
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "ADC.h"

void port_config (void)
{
	lcd_port_config();
	adc_pin_config();
}

void init_devices (void)
{
	cli(); //Clears the global interrupts
	lcd_start();
	adc_config();
	sei();   //Enables the global interrupts
}

int main(void)
{
	port_config();
	init_devices();
    int val;
	char channel0 = 0;
	
    while (1) 
    {
		val = read_adc_channel(channel0);
		lcd_print(1, 1 , val, 4);
		_delay_ms(500);
    }
}

