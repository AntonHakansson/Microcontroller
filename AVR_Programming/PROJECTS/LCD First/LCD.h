#ifndef LCD
#define LCD

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define MrLCDsDataBus		 	PORTB
#define MrLCDsDataBus_DataDir	DDRB
#define MrLCDsControl 			PORTD
#define MrLCDsControl_DataDir	DDRD

#define IntructionOrData 		0
#define ReadWrite				1
#define LightSwitch 			2

char firstColumnPos[2] = { 0, 64 };

void InitLCD(void);
void CheckIfBusy(void);
void Peek_A_Boo(void);
void SendCommand(unsigned char command);
void SendChar(unsigned char character);
void SendString(char* string);
void DrawString(uint8_t x, uint8_t y, char* string);
void DrawNum(uint8_t x, uint8_t y, int num, char numDigits);
void SetCursorPos(uint8_t x, uint8_t y);

void InitLCD()
{
	MrLCDsControl_DataDir |= (1<<LightSwitch) | (1 <<ReadWrite)  | (1 << IntructionOrData);
	_delay_ms(30);
	
	SendCommand(0b00000001); //Cleare screen
	_delay_ms(5);
	SendCommand(0b00111000); //set 8-bit length, 2-line (0b00111000)
		//SendCommand(0b00101000); //set 4-bit length, 2-line (0b00111000)
	_delay_ms(5);	
	SendCommand(0b00001110); //set display and cursor on but blink off
	_delay_ms(5);
}

void CheckIfBusy()
{
	MrLCDsDataBus_DataDir = 0;
	
	MrLCDsControl |= (1<<ReadWrite);
	MrLCDsControl &= ~(1<<IntructionOrData);
	
	while(MrLCDsDataBus >= 0x80) //if DB7 is 1 it's busy(0x80 or 0b10000000)
	{
		Peek_A_Boo();
	}
	
	MrLCDsDataBus_DataDir = 0xFF;	//ob11111111
}


void Peek_A_Boo()
{
	
	MrLCDsControl |= 1<<LightSwitch;
	asm volatile ("nop");
	asm volatile ("nop");
	MrLCDsControl &= ~(1<<LightSwitch);
}

void SendCommand(unsigned char command)
{

	CheckIfBusy();
	MrLCDsControl &= ~((1<<ReadWrite) | (1<<IntructionOrData));
	MrLCDsDataBus = command;
	Peek_A_Boo();

	MrLCDsDataBus = 0;
}

void SendChar(unsigned char character)
{
	CheckIfBusy();
	MrLCDsDataBus = character;
	MrLCDsControl &= ~(1<<ReadWrite);
	MrLCDsControl |= (1<<IntructionOrData);
	Peek_A_Boo();
	
	MrLCDsDataBus = 0;
}

void SendString(char* string)
{
	while(*string > 0)
	{
		SendChar(*string++);
	}
}

void DrawString(uint8_t x, uint8_t y, char* string)
{
	SetCursorPos(x, y);
	SendString(string);
}

void DrawNum(uint8_t x, uint8_t y, int num, char numDigits)
{	
	char tmpBuffer[numDigits+1];
	itoa(num, tmpBuffer, 10);
	for(int i=0; i<numDigits+1; i++) DrawString(x+i, y, " ");
	DrawString(x, y, tmpBuffer);
}


void SetCursorPos(uint8_t x, uint8_t y)
{
	SendCommand(0x80 + firstColumnPos[y-1]+(x-1));
}


#endif