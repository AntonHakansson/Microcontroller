#ifndef ButtonPress
#define ButtonPress

#include <avr/io.h>

char isPressed[numberOfButtons];
int Pressed_Confidence_Level[numberOfButtons];
int Released_Confidence_Level[numberOfButtons];

char ButtonDown(unsigned char pinofButton, unsigned char portBit)
{
	if(bit_is_clear(pinofButton,  portBit))
		{
			return 1;
		}
		
	return 0;
}

char ButtonPressed(int buttonNumber, unsigned char pinofButton, unsigned char portBit, int confidenceLevel)
{
	if(bit_is_clear(pinofButton,  portBit))
	{
		Pressed_Confidence_Level[buttonNumber]++;
		Released_Confidence_Level[buttonNumber] = 0;
		if(Pressed_Confidence_Level[buttonNumber] > confidenceLevel)
		{
			if(isPressed[buttonNumber] == 0)
			{

				isPressed[buttonNumber] = 1;
				return 1;
			}
			
			Pressed_Confidence_Level[buttonNumber] = 0;
		}
	}
	else
	{
		Released_Confidence_Level[buttonNumber]++;
		Pressed_Confidence_Level[buttonNumber] = 0;
		if(Released_Confidence_Level[buttonNumber] > confidenceLevel)
		{
			isPressed[buttonNumber] = 0;
			
			Released_Confidence_Level[buttonNumber] = 0;
		}
	}
	
	return 0;
}

#endif