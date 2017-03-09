#define ClockData PORTB.F7 	// 0 -> 1 = clockar in data
#define DataLine PORTB.F6	// 0 || 1 = data att clocka in
#define OutputData PORTB.F5 // 0 -> 1 =

void DisplayNum(int num)
{
	char i;
	int number;
	switch(num)
	{
		case 1:
			number = 0b10000010;
			break;
		case 2:
			number = 0b11011100;
			break;
		case 3:
			number = 0b11010110;
			break;
		case 4:
			number = 0b10110010;
			break;
		case 5:
			number = 0b01110110;
			break;
		case 6:
			number = 0b01111110;
			break;
		case 7:
			number = 0b11000010;
			break;
		case 8:
			number = 0b11111110;
			break;
		case 9:
			number = 0b11110010;
			break;
	}

	for(i =0; i<8; i++)
	{
		ClockData = 0;
		DataLine = (number & (1<<i))? 1 : 0;
		ClockData = 1;
	}

	OutputData = 0;
	OutputData = 1;

}