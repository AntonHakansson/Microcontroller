

int ButtonConfidenceLevel[NUM_BUTTONS];

void ButtonPressed(??? port, char pin, char button, char state, char confidenceLevel)
{
	
	
	ButtonConfidenceLevel[button]++;
}


