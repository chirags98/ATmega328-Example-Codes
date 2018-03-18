/*
 * LCD.c
 *
 * Created: 17-03-2018 02:34:14 PM
 * Author : Chirag
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

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
	
	lcd_string2(1, 1, "Hello World");
}