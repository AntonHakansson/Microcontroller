#ifndef ButtonGrid
#define ButtonGrid

#include <avr/io.h>
#include "myutils.h"

#define KEYPAD B  //KEYPAD IS ATTACHED ON PORTB

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR  DDR(KEYPAD)
#define KEYPAD_PIN  PIN(KEYPAD)
//*******************************

uint8_t isPressed;

uint8_t GetKeyPressed(uint8_t numCollums, uint8_t numRows);


uint8_t GetKeyPressed(uint8_t numCollums, uint8_t numRows)
{
	uint8_t numButtonGridPins = numCollums+numRows;
	
	for(uint8_t i=0; i<numRows; i++)
		KEYPAD_PORT |= 1<<i;
	
	for(uint8_t c=0; c<numCollums; c++)
	{
		for(uint8_t i=0; i<numButtonGridPins; i++)
			KEYPAD_DDR &= ~(1<<i);
		
		KEYPAD_DDR |= ((1<<(numButtonGridPins-1)) >> c);
	
		for(uint8_t r=0; r<numRows; r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				if(isPressed == 0)
				{
					isPressed = 1;
					return ((numCollums*numRows-1)-(r*numCollums+c));
				}
			}
			else
			{
				isPressed = 0;
			}
		}
	}
	
	
	return 0xFF; //indicate no keypress
}


#endif