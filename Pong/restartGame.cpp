#include "restartGame.h"

void restartGame(Hits& hits, Rectangle& ball, Rectangle& rectangle1, Rectangle& rectangle2, Magnitudes& Ball, Magnitudes rectangles, bool& firstMoove, bool& gameActive)
{
    // Set everything as false to restart the game 

    hits.leftWall = false;
    hits.rightWall = false;
    firstMoove = true;
  
    Ball.up = false;
    Ball.right = false;
    Ball.left = false;
    Ball.down = false;

    gameActive = false;

    // Ball and paddle will go to the initial positions

    ball.x = (Ball.width);
    ball.y = (Ball.height);

    rectangle1.x = 50;
    rectangle1.y = GetScreenHeight() / 2 - rectangles.height;

    rectangle2.x = GetScreenWidth() - 75;
    rectangle2.y = GetScreenHeight() / 2 - rectangles.height;
}