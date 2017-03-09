#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "ButtonGrid.h"
#include "LCD4bit.h"

int main(void)
{
	InitLCD();
	uint8_t result;
	
	while(1)
	{
		result = GetKeyPressed(3, 4);
		
		DrawNum(1, 1, result, 3);
	}
	
	
	return(0);
}