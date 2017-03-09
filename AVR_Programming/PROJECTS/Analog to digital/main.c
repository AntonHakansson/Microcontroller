#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	
	DDRD |= 0b0001111;
	
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
	int adcResult = 0;
		
	for(int i=0; i<11; ++i)
	{	
		if(ADCH > 255*(17-i)/17)
		{	
			adcResult = i-1;
			break;
		}
	}
		
	char buff[4];
	
	for (int i = 0; i < 4; ++i) {  // assuming a 4 bit int
		buff[i] = adcResult & (1 << i) ? 1 : 0;
	}
	
	for(int i=0; i<4; i++)
	{
		if(buff[i] == 1)
		{
			PORTD |= (1 << i);
		}
		else
		{
			PORTD &= ~(1 << i);
		}
	}
	
	
	ADCSRA |= 1 << ADSC;
}