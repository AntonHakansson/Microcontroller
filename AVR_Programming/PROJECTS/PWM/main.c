#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
	/**
	 * We will be using OCR1A as our PWM output which is the
	 * same pin as PB1.
	 */
	DDRB |= (1 << PINB1);

	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	ICR1 = 19999;

	OCR1A = ICR1 - 2000;

	while(1)
	{

	}

	return 0;
}
