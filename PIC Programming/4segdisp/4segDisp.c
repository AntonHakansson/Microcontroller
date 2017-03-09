void init()
{
        OSCCON = 0b01110111;
        ANSEL = 0;
        ANSELH = 0;

        TRISB = 0;
        TRISC = 0;
}

char getNumBin(char num)
{
        if(num==1) return 0b00000110;
        if(num==2) return 0b01011011;
        if(num==3) return 0b01001111;
        if(num==4) return 0b01100110;
        if(num==5) return 0b01101101;
        if(num==6) return 0b01111100;
        if(num==7) return 0b00000111;
        if(num==8) return 0b01111111;
        if(num==9) return 0b01100111;
        
        return 0b00111111;
}

void displayNum(int num)
{
        static char digit = 0;

        PORTB = getNumBin((num/(int)pow(10, 3-digit))%10);
        PORTC =  ~(0b10000000 >> digit);

        digit = ++digit%4;
}

void main()
{
        init();
        while(1)
        {
        displayNum(0005);
        }
}