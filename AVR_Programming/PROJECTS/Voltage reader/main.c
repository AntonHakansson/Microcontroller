#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	
	DDRB |= 0b0000001;
	
	ADMUX |= 1 << REFS0; //Set reference voltave to AVcc
	ADMUX |= 1 << ADLAR; //8-bit value
	
	ADCSRA |= 1<<ADEN; //ADC enable
	ADCSRA |= 1 << ADPS2; //(64) division factor between the system clock frequency and the input clockto the ADC.
	ADCSRA |= 1 << ADIE; //interrupt enable( in order to to call ISR(ADC_vect) )
	
	
	sei();	
	
	ADCSRA |= 1 << ADSC;
	
	while(1)
	{
		
	}

	return 0;
}


ISR(ADC_vect)
{		
	if(ADCH < 3.38/5*255)
		PORTB ^= 1 << PINB0;
		
	ADCSRA |= 1 << ADSC;
}