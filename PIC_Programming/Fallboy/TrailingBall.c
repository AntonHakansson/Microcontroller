#define ballBodyCount 2
typedef struct TrailingBall
{
        Vec3 body[ballBodyCount];
        char alive;
} TrailingBall;
unsigned int dropSpeed = 500;
unsigned int newBallDuration = 5000;

#define BallAmount 10
TrailingBall balls[BallAmount];

enum
{
	ADD_BALL = 0,
	BALL_DROP,
	NUM_TIMERS
} TimersID;
Timer Timers[NUM_TIMERS];

void SetBodyPos(Vec3* body, char x, char y, char z)
{
	char i;
	for(i=0; i<ballBodyCount; ++i)	// Iterate over body parts
	{
		body[i].x = x;		// Set x-position
		body[i].z = z;		// Set z-position
		body[i].y = y+i;	// Set y-position - body parts one step above the previous
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

        for(i = 1; i<ballBodyCount; i++)	// Iterate over following body-parts
        {
			if(ball->body[0].y+i < Y_DIM && ball->body[0].y+i >= 0)	// Only display if current body part is inside cube
				LEDMatrix[ball->body[i].x][ball->body[i].y][ball->body[i].z] = 1;	// Display body part
        }
}

void ResetBall(TrailingBall* ball)
{
	char k;
	ball->alive = 0;	// Set ball as dead
	for(k=0; k<ballBodyCount; k++)	//	Iterate over bodyparts
		ball->body[k].x = ball->body[k].y = ball->body[k].z = 0; // Set body parts positions to zero.
}

void ResetBalls()
{
	char i;
	for(i=0; i<BallAmount; i++)	// Iterate over balls
		ResetBall(balls+i);		// Reset all balls
}

void UpdateBall(TrailingBall* ball)
{

	if(Timers[BALL_DROP].OnDelayReached){

		if(ball->body[0].y < 0)
			SetBodyPos(ball->body, rand()%X_DIM, 3, rand()%Z_DIM);
		else
			SetBodyPos(ball->body, ball->body[0].x, ball->body[0].y-1, ball->body[0].z);
	}
	DisplayBall(ball);
}

void UpdateBalls()
{
	char i;

	if(Timers[ADD_BALL].OnDelayReached)
	{
		AddBall(random()%X_DIM, 3, random()%Z_DIM);
		Timers[BALL_DROP].duration -= 18;
		if(Timers[BALL_DROP].duration < 50)
			Timers[BALL_DROP].duration = 50;
	}
     for(i=0; i<BallAmount; ++i)
	 {
		if(balls[i].alive) UpdateBall(balls+i);
	 }
}