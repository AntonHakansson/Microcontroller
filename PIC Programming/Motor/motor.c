void init();

void main()
{
     init();

     while(1)
     {
      PORTB = 0b00000010;
      delay_ms(500);
      PORTB = 0b00000000;
      delay_ms(200);
      PORTB = 0b00000100;
      delay_ms(500);
      PORTB = 0b00000000;
      delay_ms(200);
     }
}


void init()
{
     OSCCON = 0b01110111;        // Set Clock Frequency 8Mhz
      ANSELH = 0b00000000;        // No anolog inputs
   ANSEL = 0b00000000;                // No anolog input
   
    C1ON_bit = 0;                       // Disable comparators
  C2ON_bit = 0;
   
   
   PORTC = 0;                          // set PORTC to 0
   TRISC = 0;                          // designate PORTC pins as output
   TRISB = 0;
   
   PWM1_Init(38000);
   PWM1_Start();
   PWM1_Set_Duty(127);
}