void init()
{
        OSCCON = 0b01110111;
        ADCON1 = 0b10000000;
        ANSEL = 0b00000010;
        ANSELH = 0;

        TRISA = 0xff;
        TRISB = 0;
        TRISC = 0;
}

void main()
{
unsigned ad1;
init();
 while(1)
 {
         ad1 = Adc_Read(1);
         
         ad1 = ad1 >> 2;
         
         PORTB = ad1;
 }
}