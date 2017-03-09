#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
	sei();
	
	DDRB |= 1 << PIND0;
	
	TCCR1B |= (1 << CS10) | (1 << CS11) | (1 << WGM12);
	TIMSK1 |= 1 << OCIE1A;
	OCR1A = 15624;
	
	while(1)
	{
		
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 1 << PINB0;
}