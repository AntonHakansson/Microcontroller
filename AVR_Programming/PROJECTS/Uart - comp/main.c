#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "LCD4bit.h"

volatile unsigned char reveivedByte; 

void sendString(char* string)
{
	while(*string > 0)
	{
		TransmitUART(*string++);
	}
}

int main(void)
{
	InitLCD();
	DDRB |= (1 << PINB0);
	
	InitUART(9600, 0, 8, NONE, 1, TRUE);
	
	ClearScreen();
	
	sei();
	
	while(1)
	{
		sendString("shrek is love shrek is life. ");
				
		_delay_ms(2000);
	}

	return 0;
}

ISR(USART_RXC_vect)
{
	DrawString(1, 1, "Hell");
	PORTB ^= (1 << PINB0);
}