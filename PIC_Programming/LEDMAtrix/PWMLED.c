void init()
{
        OSCCON = 0b01110111;
        ADCON1 = 0b10000000;
        ANSEL = 0b00000010;
        ANSELH = 0;
        
        Pwm1_Init(38000);
    //    Pwm1_Set_Duty(127);
        Pwm1_Start();

        TRISA = 0xff;
        TRISB = 0;
        TRISC = 0x00;
}

void main() {
unsigned int ad1;
     init();
     while(1)
     {
              ad1 = Adc_Read(1)>>2;
              PORTB = ad1;
              Pwm1_Set_Duty(0);

              if(TRISA.F2)
                       Pwm1_Set_Duty(127);

               
              Delay_ms(5);
     }
}