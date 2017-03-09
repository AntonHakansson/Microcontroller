#ifndef UART
#define UART 

#define EVEN 0
#define ODD 1
#define NONE 2

#define TRUE 1
#define FALSE 0

#include <avr/io.h>
#include <math.h>

unsigned char RecieveUART(void)
{
	while ((UCSRA & (1 << RXC)) == 0 );

	return UDR;
}

void TransmitUART(unsigned int data)
{
	//Wait until the Transmitter is ready
	while (!( UCSRA & (1<<UDRE))); 

	//Get that data outa here!
	UDR = data;
}


void InitUART(int baud, char AsyncDoubleSpeed, char dataBitLength, char ParityEvenorOdd, char stopBits, char USARTInterruptEnable)
{

	uint16_t UBBRValue = lrint(( F_CPU / (16UL * baud) ) - 1);
	
	if(AsyncDoubleSpeed == 1)
		UCSRA = (1 << U2X); //setting the U2X bit to 1 for double speed asynchronous
	
	//Put the remaining part of the baud number here
	UBRRL = UBBRValue; 
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (UBBRValue >> 8);

	//Enable the receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);
	
	//Enable interrupts
	if(USARTInterruptEnable == TRUE)UCSRB |= (1 << RXCIE);
	
	//Set 2 stop bits
	if(stopBits == 2) UCSRC |= (1 << USBS); //Sets 2 stop bits
	
	
	
	if(dataBitLength == 6) UCSRC |= (1 << UCSZ0); //6-bit data length
	if(dataBitLength == 7) UCSRC |= (1 << UCSZ1); //7-bit data length, or
	//if(dataBitLength == 8) UCSRC |= (1 << UCSZ0) | (1 << UCSZ1) ; //code for 8-bit data length
	if(dataBitLength == 9) UCSRC |= (7 << UCSZ0); //Alternative code for 9-bit data length
	
	
	if(ParityEvenorOdd == EVEN) UCSRC |= (1 << UPM1); //Sets parity to EVEN
	if(ParityEvenorOdd == ODD) UCSRC |= (3 << UPM0); //set parity to ODD
}

#endif