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

int quickPow10(int exp)
{
 static int Res[] = {1, 10, 100, 1000};

 return Res[exp];
}

char DigitLength(int num)
{
        if(num < 10)
                return 1;
        if(num < 100)
                return 2;
        if(num < 1000)
                return 3;
        if(num < 10000)
                return 4;
}

void displayNum(int num)
{
        static char digit = 0;
        char numToDisplay = 0;
        digit %= DigitLength(num);

        numToDisplay = (num/quickPow10(digit))%10;
        PORTB = getNumBin(numToDisplay);
        PORTC =  ~(1 << digit+4);

        ++digit;
}


void main()
{

 int clk = 0;
 int tick = 0;
        init();
        while(1)
        {
                if(T0IF)
                {
                        tick = 0;
                        clk == ++clk%9999;
                }
                
                
                displayNum(clk);
        }
}