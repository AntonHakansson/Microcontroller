#define assignPins(clock) \
X(f6, f0, clock)\
X(f5, f1, clock) \
X(f4, f2, clock)  \
X(f3, f3, clock)  \
X(f2, f4, clock)  \
X(f1, f5, clock)  \
X(f0, f7, clock)  \

#define X(pin1, pin2, clock) PORTB.pin1 = (PORTA.pin2 | PORTA.f7) & clock;


void init()
{
    TRISA=0b11111111;
    TRISB=0b00000000;
    TRISC=0b00000000;
    OSCCON=0b01110111;
    ANSEL=0;
    ANSELH=0;
}

void main() 
{
  char clk = 0;
  init();

  PORTB = 0;
  while(1)
  {
   clk ^= 1;
   assignPins(clk)
   Delay_ms(200);
  }
}