#include <avr/io.h>
#include <util/delay.h>

#include "LCD4bit.h"


int main(void)
{
	InitLCD();
	
	while(1)
	{
		for(int y=1; y<=2; y++)
		{
			for(int x=1; x<=20; x++)
			{	
				
				DrawString(x, y, "X");
				
				DrawString(14, 1, "X = ");
				DrawNum(18, 1, x, 2);
				
				DrawString(14, 2, "Y = ");
				DrawNum(18, 2, y, 1);
				
				_delay_ms(50);
				
				DrawString(x, y, " ");
			}
		}
	}
	
	
	return(0);
}