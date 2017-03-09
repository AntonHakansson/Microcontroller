#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
        DDRB |= 1 << PINB0; // LED on PB0
        
        while(1) {
                PORTB  ^= 1 << PINB0; // Turn LED on
				_delay_ms(1000);
        }

        return 1;
}