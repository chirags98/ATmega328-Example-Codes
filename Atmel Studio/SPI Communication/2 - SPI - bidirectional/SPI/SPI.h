/*
 * SPI.h
 *
 * Created: 15-10-2019 4.40.38 PM
 *  Author: ADMIN
 */ 


#ifndef SPI_H_
#define SPI_H_

void spiInitMaster();
void spiInitSlave();
int spiReceive(char dataOut);
int spiTransmit(char dataOut, int slavePin);

#endif /* SPI_H_ */