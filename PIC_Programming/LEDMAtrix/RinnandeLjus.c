
#define X_DIM 3
#define Y_DIM 3
#define Z_DIM 3

void init()
{
	OSCCON = 0b01110111;      //8Mhz
	ANSEL = 0;                //Digital
	ANSELH = 0;               //Digital

	TRISA = 0;       //PORTA utgång
	TRISB = 0;
	TRISC = 0;       //PORTC utgång
	PORTB = 0;
}

char PIN_STATUS[X_DIM][Y_DIM][Z_DIM];

//indexing start at 0
void setPin(char x, char y, char z, char clearPins)
{
	PIN_STATUS[x%X_DIM][y%Y_DIM][z%Z_DIM] = 1;
}

void OutputPin()
{
    char x, y, z;

	for(y=0; y<Y_DIM; y++)
		for(z=0; z<Z_DIM; z++)
			for(x=0; x<Y_DIM; x++)
				if(PIN_STATUS[x][y][z])
				{
					PORTC = PORTB = PORTA = 0;

					if(z>=2)
						PORTB = (1<<x);
					else
						PORTA = (1 <<(x+z*Z_DIM));

					PORTC = ~(1 << y);
				}
}

void resetPins()
{
	char x, y, z;
	for(y=0; y<Y_DIM; y++)
		for(z=0; z<Z_DIM; z++)
			for(x=0; x<Y_DIM; x++)
				PIN_STATUS[x][y][z] = 0;
	PORTC = PORTB = PORTA = 0;
}

unsigned int seq()
{
	static unsigned int firstTerm = 0;
	static unsigned int SecTerm = 0;
	int retVal;
	if(!SecTerm)
		return ++SecTerm;

	retVal = firstTerm+SecTerm;
	firstTerm = SecTerm;
	SecTerm = retVal;

	return retVal;
}


void main()
{
	char x, y, z;
	int nTime;
	char tmp;
	char i = 0;
	init();

	resetPins();

    while(1)
    {
		for(y=0; y<Y_DIM; y++)
			for(z=0; z<Z_DIM; z++)
				for(x=0; x<X_DIM; x++){
					if(!y%2 && x%2) setPin(x, y, z, 1);
				}

		tmp++;

		nTime = 200;
		while(nTime-- > 0)
			OutputPin();

		resetPins();
    }
}