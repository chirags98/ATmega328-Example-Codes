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

volatile unsigned int adc_val[6];

void adc_pin_config (void)
{
	DDRC = 0x00; //set PORTF direction as input
	PORTC = 0x00; //set PORTF pins floating
}

void adc_config(void)
{
	ADCSRA=0x8F;	//1 --- 1 111 ADC Enable, ADC Interrupt enable, ADC Prescaler=128
	SMCR |= 0x02;	//---- 001 0 ADC Noise Reduction mode, sleep enable/disable
}

void read_adc()
{	
	set_sleep_mode (SLEEP_MODE_ADC);
	sleep_enable();
	// Enter Sleep Mode To Trigger ADC Measurement
	// CPU Will Wake Up From ADC Interrupt
	sleep_cpu();
	sleep_disable();
}

unsigned int update_adc_channel(unsigned char channel)
{
	if (channel>=0 && channel<=7)
	{	
		//ADMUX = 0x00 | channel;	//00 - - AREF, Internal Vref turned off :--: 0000  ADC 0 (Channel)
		ADMUX = 0x40 | channel;	//01 - - AVCC reference, Internal Vref turned off :--: 0000  ADC 0 (Channel)
		_delay_ms(1);
		read_adc();
	}
	return adc_val[channel];
}

unsigned int avg_read_adc_channel(unsigned char channel, unsigned char i)
{
	float val = 0;
	
	for(int j = 1;j<=i;j++)
	{
		update_adc_channel(channel);
		val = val + adc_val[channel];
	}
	
	adc_val[channel] = val/i;
	
	return adc_val[channel];
}

//Conversion complete 
ISR(ADC_vect)
{
	unsigned char channel = ADMUX & 0x0F;	//Read channel number by masking upper nibble
	
	//ADIF is automatically cleared by writing a logical one to the flag.
	//Read ADC value
	unsigned char low = ADCL;
	unsigned char high = ADCH;
	
	adc_val[channel] = 0x03 && high;
	adc_val[channel] = adc_val[channel]<<8;
	adc_val[channel] = 256*high + low;
}