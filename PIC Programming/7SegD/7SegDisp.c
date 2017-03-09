
void init()
{
	OSCCON = 0b01110111;      //8Mhz
	ANSEL = 0;                //Digital
	ANSELH = 0;               //Digital

	TRISB = 0;			//PORTB utg
	TRISA = 0xff;       //PORTA ingång
	PORTA = 0;
}

char getNumBin(char num)
{
	switch(num)
		{
			case 1:
				return 0b00000110;
				break;
			case 2:
				return 0b01011011;
				break;
			case 3:
				return 0b01001111;
				break;
			case 4:
				return 0b01100110;
				break;
			case 5:
				return 0b01101101;
				break;
			case 6:
				return 0b01111100;
				break;
			case 7:
				return 0b00000111;
				break;
			case 8:
				return 0b01111111;
				break;
			case 9:
				return 0b01100111;
				break;
			default:
				return 0b00111111;
				break;
		}
}

void roll()
{
	char clk = 0;
	while(PORTA.f0 == 1)
	{
		PORTB = getNumBin(rand()%10);

		if(clk >= 9)
			clk = 0;

		Delay_ms(350);
	}
}


void main()
{
    srand(1);
	init();

	getNumBin(0);
	while(1)
	{
		roll();
	}
}