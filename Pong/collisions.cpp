#include "header.h"
#include "ball.h"

void collisions(Rectangle& ball, Rectangle& rectangle1, Rectangle& rectangle2, Hits& hits, bool& collision, Magnitudes& Ball)
{
	// Update ball and check where it landed 

	if (Ball.left == true && Ball.up == true)
	{
		collision = CheckCollisionRecs(ball, rectangle1);

		if (ball.x <= 0) hits.leftWall = true; // Player1 side		
		else if (ball.y <= 0) ballGoingFromUpToDown(Ball); // Cieling	
		else if (collision) ballGoingFromLeftToRight(Ball);		

		ballUpperLeft(Ball, ball);
	}
	else if (Ball.left == true && Ball.down == true)
	{
		collision = CheckCollisionRecs(ball, rectangle1);

		if (ball.x <= 0) hits.leftWall = true; // Player1 side		
		else if (ball.y >= GetScreenHeight()) ballGoingFromDownToUp(Ball); // Floor		
		else if (collision) ballGoingFromLeftToRight(Ball);			

		ballLowerLeft(Ball, ball);
	}
	else if (Ball.right == true && Ball.up == true)
	{
		collision = CheckCollisionRecs(ball, rectangle2);

		if (ball.x >= GetScreenWidth()) hits.rightWall = true; // Player2 side		
		else if (ball.y <= 0) ballGoingFromUpToDown(Ball); // Cieling		
		else if (collision) ballGoingFromRightToLeft(Ball);		

		ballUpperRight(Ball, ball);
	}
	else
	{
		collision = CheckCollisionRecs(ball, rectangle2);

		if (ball.x >= GetScreenWidth()) hits.rightWall = true; // Player2 side		
		else if (ball.y >= GetScreenHeight()) ballGoingFromDownToUp(Ball); // Floor		
		else if (collision) ballGoingFromRightToLeft(Ball);		

		ballLowerRight(Ball, ball);
	}
	
}