#include "ball.h"


void ballUpperRight(Magnitudes& Ball, Rectangle& ball)
{
	ball.x += Ball.speed;
	ball.y -= Ball.speed;

}
void ballUpperLeft(Magnitudes& Ball, Rectangle& ball)
{
	ball.x -= Ball.speed;
	ball.y -= Ball.speed;

}
void ballLowerRight(Magnitudes& Ball, Rectangle& ball)
{
	ball.x += Ball.speed;
	ball.y += Ball.speed;

}
void ballLowerLeft(Magnitudes& Ball, Rectangle& ball)
{
	ball.x -= Ball.speed;
	ball.y += Ball.speed;

}
void ballGoingFromLeftToRight(Magnitudes& Ball)
{
	Ball.left = false;
	Ball.right = true;
}
void ballGoingFromRightToLeft(Magnitudes& Ball)
{
	Ball.right = false;
	Ball.left = true;
}
void ballGoingFromUpToDown(Magnitudes& Ball)
{
	Ball.up = false;
	Ball.down = true;
}
void ballGoingFromDownToUp(Magnitudes& Ball)
{
	Ball.down = false;
	Ball.up = true;
}