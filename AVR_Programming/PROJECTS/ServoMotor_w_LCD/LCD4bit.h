#ifndef LCD
#define LCD

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCDsPort			 	PORTD
#define LCD_DataDir				DDRD

#define lcd_D4_bit				0
#define lcd_D5_bit				1
#define lcd_D6_bit				2
#define lcd_D7_bit				3

#define lcd_RS_bit 				4
#define lcd_RW_bit				5
#define lcd_E_bit 				6


// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position

char firstColumnPos[2] = { 0, 64 };

void InitLCD(void);
void CheckIfBusy(void);
void Peek_A_Boo(void);
void lcdWriteInstruction_4d(uint8_t theInstruction);
void lcdWrite4(uint8_t theByte);
void SendCommand(unsigned char command);
void SendChar(unsigned char character);
void SendString(char* string);
void DrawString(uint8_t x, uint8_t y, char* string);
void DrawNum(uint8_t x, uint8_t y, int num, char numDigits);
void SetCursorPos(uint8_t x, uint8_t y);

void InitLCD()
{
	LCD_DataDir |= 0xFF;
	_delay_ms(100);
	LCDsPort &= ~(1 << lcd_E_bit);
	LCDsPort &= ~(1 << lcd_RS_bit);
	
	lcdWrite4(lcd_FunctionReset);
	_delay_ms(10);
	lcdWrite4(lcd_FunctionReset);
	_delay_ms(200);
	lcdWrite4(lcd_FunctionReset);
	_delay_ms(200);
	
	lcdWrite4(lcd_FunctionSet4bit);               // set 4-bit mode
    _delay_us(80);                                // 40uS delay (min)
	
	lcdWriteInstruction_4d(lcd_FunctionSet4bit);  //set mode, lines, and font
	_delay_us(80); 
	
	// Display On/Off Control instruction
    lcdWriteInstruction_4d(lcd_DisplayOff);        // turn display OFF
    _delay_us(80);                                  // 40uS delay (min)

	// Clear Display instruction
    lcdWriteInstruction_4d(lcd_Clear);             // clear display RAM
    _delay_ms(4);                                   // 1.64 mS delay (min)

	// ; Entry Mode Set instruction
    lcdWriteInstruction_4d(lcd_EntryMode);         // set desired shift characteristics
    _delay_us(80);                                  // 40uS delay (min)
 
	// Display On/Off Control instruction
    lcdWriteInstruction_4d(lcd_DisplayOn);         // turn the display ON
    _delay_us(80);                                  // 40uS delay (min)
}

void CheckIfBusy()
{
	/*LCD_DataDir &= ~((1 << PORT0) | (1 << PORT1) | (1 << PORT2) | (1 << PORT3));
	
	LCDsPort |= (1<<ReadWrite);
	LCDsPort &= ~(1<<IntructionOrData);
	
	while((LCDsPort&0x0F) >= 0x8) //if DB7 is 1 it's busy
	{
		Peek_A_Boo();
	}
	
	LCD_DataDir |= (1 << PORT0) | (1 << PORT1) | (1 << PORT2) | (1 << PORT3);*/
}


void Peek_A_Boo()
{
	
	LCDsPort |= 1<<lcd_E_bit;
	asm volatile ("nop");
	asm volatile ("nop");
	LCDsPort &= ~(1<<lcd_E_bit);
}

void lcdWriteInstruction_4d(uint8_t theInstruction)
{
    LCDsPort &= ~(1<<lcd_RS_bit);                // select the Instruction Register (RS low)
    LCDsPort &= ~(1<<lcd_E_bit);                  // make sure E is initially low
    lcdWrite4(theInstruction);                    // write the upper 4-bits of the data
    lcdWrite4(theInstruction << 4);               // write the lower 4-bits of the data
}

void lcdWrite4(uint8_t command)
{
	LCDsPort &= ~(1 << lcd_D7_bit);					//Assume data is '0'
	if(command & 1<<7) LCDsPort |= (1 << lcd_D7_bit);	//makee data = '1' if necessary
	
	LCDsPort &= ~(1 << lcd_D6_bit);					//Assume data is '0'
	if(command & 1<<6) LCDsPort |= (1 << lcd_D6_bit);	//makee data = '1' if necessary
	
	LCDsPort &= ~(1 << lcd_D5_bit);					//Assume data is '0'
	if(command & 1<<5) LCDsPort |= (1 << lcd_D5_bit);	//makee data = '1' if necessary
	
	LCDsPort &= ~(1 << lcd_D4_bit);					//Assume data is '0'
	if(command & 1<<4) LCDsPort |= (1 << lcd_D4_bit);	//makee data = '1' if necessary

	//write data
	LCDsPort |= (1 << lcd_E_bit);
	_delay_us(1);
	LCDsPort &= ~(1 << lcd_E_bit);
	_delay_us(1);
}

void SendCommand(unsigned char command)
{
	
}

void SendChar(unsigned char character)
{
	LCDsPort |= (1<<lcd_RS_bit);                // select the Instruction Register (RS HIGH)
    LCDsPort &= ~(1<<lcd_E_bit);                  // make sure E is initially low
    lcdWrite4(character);                   	 // write the upper 4-bits of the data
    lcdWrite4(character << 4);             		  // write the lower 4-bits of the data
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
	lcdWriteInstruction_4d(0x80 + firstColumnPos[y-1]+(x-1));
}


#endif