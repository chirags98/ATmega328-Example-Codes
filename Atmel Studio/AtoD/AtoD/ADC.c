/*
 * ADC.c
 *
 * Created: 22-Jul-17 11:11:48 PM
 *  Author: Chirag
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define F_CPU 16000000
#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>

//ADC pin configuration
void adc_pin_config (void)
{
	DDRC = 0x00; //set PORTF direction as input
	PORTC = 0x00; //set PORTF pins floating
}

void adc_config(void)
{
	//ADCSRA=0x85; //1 --- 0 101 ADC Enable, ADC Interrupt disable, ADC Prescaler=32
	ADCSRA=0x87; //1 --- 0 111 ADC Enable, ADC Interrupt disable, ADC Prescaler=128
}

unsigned int read_adc()
{
	ADCSRA|=0x40; //ADSC: ADC Start Conversion: In Single Conversion mode, write this bit to one to start each conversion.
	while((ADCSRA & 0x10)==0); //ADIF: ADC Interrupt Flag: This bit is set when an ADC conversion completes and the Data Registers are updated.
	ADCSRA|=0x10;	//ADIF is cleared by writing a logical one to the flag.
	
	unsigned char low = ADCL;
	unsigned char high = ADCH;
	
	unsigned int val = 0x03 && high;
	val = val<<8;
	val = 256*high + low;
	
	return val;
}

unsigned int read_adc_channel(char channel)
{
	if (channel>=0 && channel<=7)
	{
		ADMUX = 0x40 | channel;	//01 - - AVCC with external capacitor at AREF pin :--: 0000  ADC 0 (Channel)
		//ADMUX = 0x00 | channel;	//00 - - AREF, Internal Vref turned off :--: 0000  ADC 0 (Channel)
		_delay_ms(5);
		return read_adc();
	}
	else
	return 22;				//error
}

unsigned int avg_read_adc_channel(char channel, char i)
{
	float val = 0;
	for(int j = 1;j<=i;j++)
	{
		val = val + read_adc_channel(channel);
	}
	val/=i;
	
	return val;
}