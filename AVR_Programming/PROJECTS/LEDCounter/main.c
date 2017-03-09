#include <avr/io.h>

int main()
{	
	//initialize the port for the leds
	DDRD = 0x01111111;
	PORTD = 0b00000000;
	TCCR1B |= (1<<CS10) | (1<<CS11); //Timer/Counter1 Control Register B(prescaler 64)
	
	uint8_t LEDNumber = 0;
	
	while(1)
	{
		if(TCNT1 > 15625) // internal clock speed:	1 000 000 MHz
						  // prescaler:			64
						  // 1 000 000/64 = 15625
		{	

			PORTD |= 1 << LEDNumber;
			if(LEDNumber > 5)
			{
				LEDNumber = 0;
				PORTD = 0b00000000;
			}else
				LEDNumber++;
	
			TCNT1 = 0;
		} 
	}
	return 0;
}