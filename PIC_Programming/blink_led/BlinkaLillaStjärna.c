void main()
{
char pin = 0;
    osccon = 0b01110111;//8Mhz
    TRISA = 0xFF;       //PORTA ing�ng
    TRISB = 0;          //PORTB utg�ng
    ANSEL = 0;          //Digital
    ANSELH = 0;         //Digital

    while(1)
    {
       if(pin >= 8) pin = 0;
       PORTB = 1 << pin++;
       Delay_ms(100);
    }
}
