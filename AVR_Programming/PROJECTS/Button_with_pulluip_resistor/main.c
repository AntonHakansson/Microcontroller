#include <avr/io.h>

int main()
{
	DDRB |= 1 << PINB0;
	
	while(1)
	{
		if(bit_is_clear(PINB, 1))
			PORTB ^= 1 << PINB0;
	}

	return 0;
}