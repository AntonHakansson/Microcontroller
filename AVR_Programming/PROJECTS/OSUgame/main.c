#define F_CPU 16000000UL
#define numberOfButtons 4

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "ButtonPress.h"
#include "myutils.h"


#define KEYPAD C  //KEYPAD IS ATTACHED ON PORTB

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR  DDR(KEYPAD)
#define KEYPAD_PIN  PIN(KEYPAD)
//*******************************

void scanKeypad()
{
	for(int c=0; c<4; c++){ 
		KEYPAD_PORT = ~(0x10<<c);
		asm volatile("nop");
		asm volatile("nop");
		
		for(int r=0; r<4; r++){
			KEYPAD_DDR = ~(1<<r);
			
			asm volatile("nop");
			asm volatile("nop");
			
			char key = (r+1)+((c+1)*10);
			if(!(KEYPAD_PIN & (1<<r))){
				TransmitUART(key); 
				PORTD |= (1<<PIND6);
			}
		}
	}
	
	PORTD &= ~(1<<PIND6);
	TransmitUART(0xF0); //tells program scan was complete
}



int main(void)
{
	InitUART(9600, 0, 8, NONE, 1, TRUE);
	TCCR1B |= (1<<CS10) | (1<<CS12); //Timer/Counter1 Control Register B(prescaler 1024) => 15625hz
	
	DDRD = (1<<PIND6);
	
	while(1)
	{		
		scanKeypad();
	}
}