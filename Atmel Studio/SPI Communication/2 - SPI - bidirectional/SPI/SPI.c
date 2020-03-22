/*
 * SPI.c
 *
 * Created: 20/12/2014 14:40:18
 *  Author: Benedict
 */

#include <avr/io.h>

#define csPort PORTB
/*
#ifndef csPORT
# warning "Define csPORT (default PORTB)"
#define csPort PORTB
#endif
*/

#define cs1 2
#ifndef cs1
# warning "Define cs1 if needed"
#define cs1 0
#endif

/*
#define cs1 2
#ifndef cs1 
# warning "Define cs1 if needed"
#define cs1 0
#endif

#ifndef cs2
# warning "Define cs2 if needed"
#define cs2 0
#endif

#ifndef cs3
# warning "Define cs3 if needed"
#define cs3 0
#endif
*/

#define sbit(reg,bit)	reg |= (1<<bit)			// Macro defined for Setting a bit of any register.
#define cbit(reg,bit)	reg &= ~(1<<bit)		// Macro defined for Clearing a bit of any register.
#define read_bit(reg, bit)	reg & (1<<bit)		// Macro defined for reading a bit of any register.

char dataIn;

void spiInitMaster(void)
{
	DDRB |= (1<<2)|(1<<3)|(1<<5);    // SCK, MOSI and SS as outputs
	DDRB &= ~(1<<4);                 // MISO as input
	
	//csPort |= (1<<cs1) | (1<<cs2) | (1<<cs3);//Set slaves high	
	
	SPCR |= (1<<MSTR);               // Set as Master
	SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128 (slowest speed)
	SPCR |= (1<<SPE);                // Enable SPI
}

void spiInitSlave(void)
{
	DDRB &= ~((1<<2)|(1<<3)|(1<<5));   // SCK, MOSI and SS as inputs
	DDRB |= (1<<4);                    // MISO as output

	SPCR &= ~(1<<MSTR);					// Set as slave
	SPCR |= (1<<SPR0)|(1<<SPR1);	    // divide clock by 128 (slowest speed)
	SPCR |= (1<<SPE);					// Enable SPI
}

int spiReceive(char dataOut)			//Call in while(1)
{	
	SPDR = dataOut;						//queue the data to be sent
	
	while(!(SPSR & (1<<SPIF)));		    // wait until all data is received
	dataIn = SPDR;
	return dataIn;
}

int spiTransmit(char dataOut, int slavePin)	//Call in while(1)
{
	//csPort &= ~ 1<<slavePin;
	cbit(csPort, cs1);
	
	SPDR = dataOut;                 //send the data
	while(!(SPSR & (1<<SPIF)));
	
	sbit(csPort, cs1);
	
	dataIn = SPDR;
	return dataIn;					//receive the data from the slave
}