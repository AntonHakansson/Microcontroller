#define F_CPU 16000000UL

#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#include "ButtonGrid.h"
#include "LCD4bit.h"

#define MultiplicationID	 9 
#define EcualID				10 

char* multString = "   ";
int8_t keyPressed;
unsigned int Factor1 = 0;
unsigned int Factor2 = 0;
unsigned int result = 0;
uint8_t comp = 255;
uint8_t mode = 0;
	
void Init(void)
{
	multString = "   ";
	keyPressed = -1;
	Factor1 = 0;
	Factor2 = 0;
	result = 0;
	comp = 255;
	mode = 0;
	
	ClearScreen();
}

unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

int notesFreq[] = {1046, 1174, 1318, 1396, 1567, 1760, 1975, 2093, 2349, 2637, 2793, 3135, 3520};

void Update(void)
{
	OCR1A = ICR1/2;	 
	if(GetKeyPressed(3, 4) != 0xFF)
		{
			keyPressed = GetKeyPressed(3, 4);
			
			DDRD |= (1 << PIND5);
						
			if(keyPressed != comp && keyPressed != MultiplicationID && keyPressed != EcualID)
			{
				ICR1 = 62500/notesFreq[keyPressed];
				
				
				if(result > 0)
				{	
					Init();
				}
					
				comp = keyPressed;
				if(mode)
				{
					Factor2 *= 10;
					Factor2 += keyPressed+1;
				}
				else
				{
					Factor1 *= 10;
					Factor1 += keyPressed+1;
				}
			}
			else if(keyPressed == MultiplicationID)
			{
				comp = keyPressed;
				mode = 1;
				multString = " * ";
			}
			else if(keyPressed == EcualID)
			{
				comp = keyPressed;
				
				result = Factor1 * Factor2;
			}
		}
		else
		{
			comp = 255;
			DDRD &= ~(1 << PIND5);
		}
		
		uint8_t numDigits1 = GetNumberOfDigits(Factor1);
		uint8_t numDigits2 = GetNumberOfDigits(Factor2);
		uint8_t numDigitsRes = GetNumberOfDigits(result);
		
		if(Factor1 > 0)DrawNum(1, 1, Factor1, numDigits1);
		DrawString(numDigits1+1, 1, multString);
		if(Factor2 > 0) DrawNum(numDigits1+4, 1, Factor2, numDigits2);
		if(result > 0)DrawNum(1, 2, result, numDigitsRes);
		
		DrawNum(15, 2, GetKeyPressed(3, 4), 1+GetNumberOfDigits(GetKeyPressed(3, 4)));
}


int main(void)
{
	InitLCD();
	
	Init();
	
	/**
	*	COM1A0 and COM1A1 set HIGH for Inverted Mode
	*	WGM11, WGM12, WGM13 set HIGHT for WaveformGenerationMode - fast pwm
	*	CS12 set HIGH for a prescaler of 256
	*/
	DDRD &= ~(1 << PIND5);
	TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12);
	
	while(1)
	{
		Update();
	}
	
	
	return(0);
}