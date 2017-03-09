#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "LCD4bit.h"

#define refresh 15625/10

double time(int pin)
{
	unsigned long count = 0, total = 0;	
	
	TCNT1 = 0;
	while(TCNT1 < refresh){
		DDRB |= (1 << pin);		//output mode
		PORTB = 0;					//discharge "capacitor"
		_delay_ms(30);
		
		DDRB &= ~(1 << pin);		//Input mode
		
		while( (PINB&(1<<pin)) == 0 ) //while reading a digital LOW do
			count++;		//count the time it takes to reach a digital HIGH
			
		total++;
	}
	
	return (count<<4) / total; //return the avrage value
}

int main(void)
{
	InitLCD();
	ClearScreen();
	
	InitUART(9600, 0, 8, NONE, 1, TRUE);
	
	TCCR1B |= (1<<CS10) | (1<<CS12); //Timer/Counter1 Control Register B(prescaler 1024) => 15625hz
	
	
	// set all pins on PORTB LOW and to output
    DDRB = 0xFF;
	PORTB = 0;
	
	DDRB &= ~(1 << PINB0);		//Input mode
	DDRB &= ~(1 << PINB1);		//Input mode
	DDRB &= ~(1 << PINB2);		//Input mode
	
	unsigned int x, y, z;
	
	while(1)
	{	
		x = time(PINB2)-600;
		TransmitUART(x);
		
		y = time(PINB0)-600 + 1*100;
		TransmitUART(y);
		
		z = time(PINB1)-600 + 2*100;
		TransmitUART(z);
	}
}
