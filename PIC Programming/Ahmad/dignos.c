void main() {
     osccon = 0b01110111;
     ANSEL = 0;
     ANSELH = 0;
     
     TRISA = 0xff;
     TRISB = 0;
     
     while(1)
     {
     PORTB.f5 = PORTA.f3;

            }
}