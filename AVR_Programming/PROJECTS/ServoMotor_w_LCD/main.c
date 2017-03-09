#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include "lcd4bit.h"

static volatile uint16_t tenBitResult;

int main(void)
{
	/**
	 * We will be using OCR1A as our PWM output which is the
	 * same pin as PB1.
	 */
	InitLCD();
	DDRB |= (1 << PINB1);
	DDRB |= (1 << PINB0);
	
	/**
	*
	*/
	
	ADMUX |= 1 << REFS0; //Set reference voltave to AVcc
	//ADMUX |= 1 << ADLAR; //8-bit value
	
	ADCSRA |= 1 << ADEN; //ADC enable
	ADCSRA |= 1 << ADPS2; //(64) division factor between the system clock frequency and the input clock to the ADC.
	ADCSRA |= 1 << ADIE; //interrupt enable( in order to to call ISR(ADC_vect) )
	
	
	sei();	
	
	ADCSRA |= 1 << ADSC;
	
	
	/**
	*	COM1A0 and COM1A1 set HIGH for Inverted Mode
	*	WGM11, WGM12, WGM13 set HIGHT for WaveformGenerationMode - fast pwm
	*	CS10 set HIGH for no prescaler
	*/
	
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	ICR1 = 20000;
	
	float k = (2300-730)/(1023);
	while(1)
	{
		OCR1A = ICR1 - ((k*tenBitResult)+730);	
		
		PORTB  ^= (1 << PINB0);
		_delay_ms(1);
	}
	
	return 0;
}

ISR(ADC_vect)
{
	uint8_t theLow = ADCL;
	tenBitResult = ADCH << 8 | theLow;
	
	DrawString(1, 1, "Us: ");
	DrawNum(8, 1, ICR1-OCR1A, 4);
		
	DrawString(1, 2, "ADCH: ");
	DrawNum(8, 2, tenBitResult, 4);
	
	ADCSRA |= 1 << ADSC;
}