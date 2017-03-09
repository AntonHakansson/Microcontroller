char isPressed[numberOfButtons];
int Pressed_Confidence_Level[numberOfButtons];
int Released_Confidence_Level[numberOfButtons];

void InitButtons()
{
	char i;
	for(i=0; i<numberOfButtons; i++)
	{
		isPressed[i] = 0;
		Pressed_Confidence_Level[i] = 0;
		Released_Confidence_Level[i] = 0;
	}
}


char ButtonPressed(int buttonNumber, char status, char expected,  int confidenceLevel)
{
	if(status == expected)
	{
		Pressed_Confidence_Level[buttonNumber]++;
		Released_Confidence_Level[buttonNumber] = 0;
		if(Pressed_Confidence_Level[buttonNumber] > confidenceLevel )
		{
			if(isPressed[buttonNumber] == 0)
			{

				isPressed[buttonNumber] = 1;
				return 1;
			}

			Pressed_Confidence_Level[buttonNumber] = 0;
		}
	}
	else
	{
		Released_Confidence_Level[buttonNumber]++;
		Pressed_Confidence_Level[buttonNumber] = 0;
		if(Released_Confidence_Level[buttonNumber] > confidenceLevel)
		{
			isPressed[buttonNumber] = 0;

			Released_Confidence_Level[buttonNumber] = 0;
		}
	}

	return 0;
}