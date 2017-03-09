#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "LCD4bit.h"

static volatile uint16_t tenBitResult;

int main(void)
{
	DDRB |= (1 << PINB1);
	
	
	ADMUX |= 1 << REFS0; //Set reference voltave to AVcc
	ADCSRA |= 1 << ADEN; //ADC enable
	ADCSRA |= 1 << ADPS2; //(64) division factor between the system clock frequency and the input clock to the ADC.
	ADCSRA |= 1 << ADIE; //interrupt enable( in order to to call ISR(ADC_vect) )
	
	sei();	
	
	InitLCD();
	
	while(1)
	{
		for(int y=1; y<=2; y++)
		{
			for(int x=1; x<=20; x++)
			{	
				
				DrawString(x, y, "X");
				
				DrawString(10, 1, "X = ");
				DrawNum(14, 1, x, 2);
				
				DrawString(10, 2, "Y = ");
				DrawNum(14, 2, y, 1);
				
				_delay_ms(190);
				
				DrawString(x, y, " ");
				_delay_ms(10);
			}
		}
	}
	
	
	return(0);
}