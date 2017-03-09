#include "Timer.c"

#define InputPort 			(PORTA)
#define PlayerLeftPin 		(0)
#define PlayerForwardPin 	(1)
#define PlayerRightPin 		(2)
#define PlayerBackwardPin 	(3)
#define ButtonConfidenceTime (100)

#define LEDDATA (PORTB.F0)
#define LEDCLK 	(PORTB.F1)
#define LEDLTCH (PORTB.F2)

#define X_DIM (4)
#define Y_DIM (4)
#define Z_DIM (4)

#define BallAmount (10)
#define BallBodyCount (2)


typedef struct Vec2
{
 signed short x;
 signed short z;
} Vec2;

typedef struct Vec3
{
 signed short x;
 signed short y;
 signed short z;
} Vec3;

typedef struct TrailingBall
{
        Vec3 body[BallBodyCount];
        char alive;
} TrailingBall;



void init();
void Endscreen();

void UpdatePlayer();
char PlayerCollided();
void Clamp(signed short* val, signed short min, signed short max);

void ClearLEDMatrix();
void UpdateLEDMatrix();

void AddBall(char x, char y, char z);
void ResetBall(TrailingBall* ball);
void ResetBalls();
void SetBodyPos(Vec3* body, char x, char y, char z);
void UpdateBall(TrailingBall* ball);
void UpdateBalls();
void DisplayBall(TrailingBall* ball);




char LEDMatrix[X_DIM][Y_DIM][Z_DIM];	// 3D array to store state of all LEDs
Vec2 PlayerPos = {0, 0};	// Variable for playerpos

int randSeed;	// Garbage value for seed
 
TrailingBall balls[BallAmount];

enum
{
	ADD_BALL = 0,
	BALL_DROP,
	NUM_TIMERS
} TimersID;
Timer Timers[NUM_TIMERS];

typedef enum GameState{
	ST_IDLE,
	ST_INGAME
} gameState;
GameState gameState = ST_IDLE;

void ChangeState(GameState newState)
{
	
	if(gameState == ST_IDLE && newState == ST_INGAME)
		srand(randSeed);
	
	if(gameState == ST_INGAME && newState == ST_IDLE)
		Endscreen();
	
	init();
	gameState = newState;
}

void main() {
	init();

	while(1)
	{
		switch(gameState)
		{
			case ST_IDLE:
				if(button(&InputPort, PlayerRightPin, ButtonConfidenceTime, 0) )
					ChangeState(ST_INGAME);
				randSeed++;
				break;
			case ST_INGAME:
				ClearLEDMatrix();
				UpdateTimers(Timers, NUM_TIMERS);
				
				UpdatePlayer();
				
				if(PlayerCollided())
					ChangeState(ST_IDLE);
					
				UpdateBalls();
				UpdateLEDMatrix();
				break;
		}
	}
}

void init()
{
	OSCCON = 0b01110111;        // Set Clock Frequency 8Mhz
	ANSELH = 0b00000000;        // No anolog inputs
	ANSEL = 0b00000000;                // No anolog inputs

	TRISA = 0xff;       // Set PortA as input
	TRISB = 0; 			// set PortB as Output;
	TRISC = 0;          //set PortC as output;

	PORTA = PORTB = PORTC = 0;  // No output
	LEDCLK = 0;   	// reset Clock pin
	LEDLTCH = 0;	// Initialize Latch pin as zero
	LEDDATA = 0;	// Initialize Data line to zero

	PlayerPos.x = PlayerPos.z = 0;	// Set player starting position

	SetTimer(&Timers[ADD_BALL], 1000);	// Initialize timer with an interval of 1000 ticks
	SetTimer(&Timers[BALL_DROP], 250);	// Initialize timer - interval of 250 ticks

	ClearLEDMatrix();	// Initialize to no output on LEDMatrix
	ResetBalls();		// Kill all balls
}

void Clamp(signed short* val, signed short min, signed short max)
{
        if(*val > 3)
                *val = 3;
        if(*val < 0)
                *val = 0;
}






void UpdatePlayer()
{
	if(button(&InputPort, PlayerRightPin, ButtonConfidenceTime, 0)) // Right button pressed
		  ++PlayerPos.z;											// Move player accordingly
	if(button(&InputPort, PlayerLeftPin, ButtonConfidenceTime, 0)) 	// Left button pressen
			--PlayerPos.z;											// Move player accordingly

	if(button(&InputPort, PlayerBackwardPin, ButtonConfidenceTime, 0)) // Back button pressed
			++PlayerPos.x;												// Move player accordingly
	if(button(&InputPort, PlayerForwardPin, ButtonConfidenceTime, 0))	// Forward button pressed
			--PlayerPos.x;												// Move player accordingly

	Clamp(&PlayerPos.x, 0, 3);	// Clamp player position between values 0-3
	Clamp(&PlayerPos.z, 0, 3);

	LEDMatrix[PlayerPos.x][0][PlayerPos.z] = 1;	// Lit LED according to player position	
}

char PlayerCollided()
{
	char i, k;
	for(i=0; i<BallAmount; i++)	// Iterate over all balls
	{
		if(balls[i].alive)	// Check if ball is alive
		{
			for(k = 0; k<BallBodyCount; k++) // Iterate over balls body-parts
				if(balls[i].body[k].y == 0 && balls[i].body[k].x == PlayerPos.x && balls[i].body[k].z == PlayerPos.z)	// baody part position equal player position ?
					return 1;	// Player collided - return true
		}
	}
	
	return 0;	// No collision occured - return false
}						


void Endscreen()
{
	char x, y, z, j;
	
	for(j=0; j<2; j++)	// Do landing strip - lightnign two times
	for(y=0; y<Y_DIM; y++)	// Iterate over Y-dimension
	{
		ClearLEDMatrix();	// Clear LEDMatrix
		for(x=0; x<X_DIM; x++)	
			for(z=0; z<Z_DIM; z++)
				LEDMatrix[x][y][z] =  1; // Set all LEDs on plane to on
			
		UpdateLEDMatrix();	// Update first row
		delay_ms(40);
		UpdateLEDMatrix();	// Update second row
		delay_ms(40);
		UpdateLEDMatrix();	// Update third row
		delay_ms(40);
		UpdateLEDMatrix();	// Update last row
		delay_ms(60);
	}
}

void AddBall(char x, char y, char z)
{
        char i;

        for(i=0; i<BallAmount; i++)	// Iterate over balls
                if(!balls[i].alive)	// Find first dead ball
                {
						balls[i].alive = 1;	// Set ball to alive
						SetBodyPos(balls[i].body, x, y, z);	// Initialize with values
						break;	// return
                }
}

void DisplayBall(TrailingBall* ball)
{
        char i;
		
        if(ball->body[0].y >= 0)	// Only display when inside XYZ dimension
			LEDMatrix[ball->body[0].x][ball->body[0].y][ball->body[0].z] = 1; // Display the first body part
		
        for(i = 1; i<BallBodyCount; i++)	// Iterate over following body-parts
        {
			if(ball->body[0].y+i < Y_DIM && ball->body[0].y+i >= 0)	// Only display if current body part is inside cube
				LEDMatrix[ball->body[i].x][ball->body[i].y][ball->body[i].z] = 1;	// Display body part
        }
}

void ResetBall(TrailingBall* ball)
{
	char k;
	ball->alive = 0;	// Set ball as dead
	for(k=0; k<BallBodyCount; k++)	//	Iterate over bodyparts
		ball->body[k].x = ball->body[k].y = ball->body[k].z = 0; // Set body parts positions to zero.
}

void ResetBalls()
{
	char i;
	for(i=0; i<BallAmount; i++)	// Iterate over balls
		ResetBall(balls+i);		// Reset all balls
}

void SetBodyPos(Vec3* body, char x, char y, char z)
{
	char i;
	for(i=0; i<BallBodyCount; ++i)	// Iterate over body parts
	{
		body[i].x = x;		// Set x-position
		body[i].z = z;		// Set z-position
		body[i].y = y+i;	// Set y-position - body parts one step above the previous
	}
}

int random()
{
	static unsigned int S;	// Seed with garbage value
	return S=(S*32719+3)%32749;	// Return a new arbitrary 
}

void UpdateBall(TrailingBall* ball)
{
	if(Timers[BALL_DROP].OnDelayReached){	// Update ball on timer interval 
		
		if(ball->body[0].y < 0)
			SetBodyPos(ball->body, rand()%X_DIM, 3, rand()%Z_DIM);	// Give ball new random position when below cube
		else
			SetBodyPos(ball->body, ball->body[0].x, ball->body[0].y-1, ball->body[0].z); // Otherwise move ball downward
	}
	DisplayBall(ball);	// Display the ball
}

static int tmp = 0;
void UpdateBalls()
{
	char i;
	
	if(Timers[ADD_BALL].OnDelayReached)	
	{
		AddBall(random()%X_DIM, 3, random()%Z_DIM); // Add new ball after interval
		Timers[BALL_DROP].duration -= 18;			// Increase ball drop speed
		if(Timers[BALL_DROP].duration < 50)			// don't allow ball speed below 50
			Timers[BALL_DROP].duration = 50;
	}
	
	for(i=0; i<BallAmount; ++i)	// iterate over all balls
	{
		if(balls[i].alive) UpdateBall(balls+i);	// Update ball if alive
	}
}






void UpdateLEDMatrix()
{
 static char curRow = 0;	// display one plane at a time
 char x, z;

        if(curRow >= Y_DIM)		// Don't allow above cube size
                curRow = 0;

        for(z=0; z<Z_DIM; ++z)
                for(x=0; x<X_DIM; ++x)
                {

						LEDCLK = 0;   // reset Clock pin
						LEDDATA = LEDMatrix[x][curRow][z];   // data to shift in
						LEDCLK = 1; // Clock data
				}
				PORTC = 1<<(4+curRow);

				LEDCLK = 0;   // reset Clock pin
				LEDLTCH = 0;	//reset latch
				LEDLTCH = 1;   // Latch, Output shift-register data

        curRow++;
}

void ClearLEDMatrix()
{
	char x, y, z;

	for(x=0; x<X_DIM; ++x)				// Iterate over X dimension	
		for(y=0; y<Y_DIM; ++y)			// Iterate over Y dimension
			for(z=0; z<Z_DIM; ++z)		// Iterate over Z dimension
				LEDMatrix[x][y][z] = 0;	// Set all values to zero
}