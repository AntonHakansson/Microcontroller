
void init()
{
     osccon = 0b01110111;
     ANSEL = ANSELH = 0;
     TRISA = 0xff;
     TRISB = TRISC = 0;
}

void dispRand(char clk)
{
  if(clk%1000 > 995)
   PORTB ^= 0b01010101;
}

void main() 
{
 init();
 
 while(1)
 {
 PORTC.F0 = 0;
  if(PORTA.f0)
  {
              PORTC.F0 = 1;
  }
 }
}