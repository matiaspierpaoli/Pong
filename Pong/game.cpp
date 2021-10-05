#include "game.h"
#include "raylib.h"
#include "ball.h"
#include <iostream>
#include "restartGame.h"

void game(Screen& screen)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    srand(time(NULL)); // random's seed

    Hits hits;

    Magnitudes rectangles;
    Magnitudes Ball; // 'ball' is used as a rectangle struct

    rectangles.width = 13;
    rectangles.height = GetScreenHeight() / 5;

    Ball.width = GetScreenWidth() / 2 - 15;
    Ball.height = GetScreenHeight() / 2 - 7;

    Rectangle rectangle1 = { 50, GetScreenHeight() / 2 - rectangles.height,  rectangles.width,  rectangles.height }; // Player 1 paddle
    Rectangle rectangle2 = { 725,  GetScreenHeight() / 2 - rectangles.height,  rectangles.width,  rectangles.height }; // Player 2 paddle
    Rectangle ball = {Ball.width, Ball.height, 15, 15 }; // Ball

    Rectangle leftArrow = { GetScreenWidth() / 2 - 60,  GetScreenHeight() / 2 - 3, 26, 5}; // Left arrow appearing only before pressing ENTER at the start of a game
    Rectangle rightArrow = { GetScreenWidth() / 2 + 19,  GetScreenHeight() / 2 - 3, 30, 5 }; // Right arrow appearing only before pressing ENTER at the start of a game

    Rectangle returnToMenuButton;
    returnToMenuButton.x = GetScreenWidth() / 2 - 300;      // 
    returnToMenuButton.y = GetScreenHeight() - 50;          //       
    returnToMenuButton.width = 240;                         //         
    returnToMenuButton.height = 30;                         //  
                                                            //
    Rectangle returnToGameButton;                           //   Simulate rectangle hitboxes where the players can click
    returnToGameButton.x = GetScreenWidth() / 2 + 50;       // 
    returnToMenuButton.y = GetScreenHeight() - 50;          // 
    returnToGameButton.y = GetScreenHeight() - 50;          //
    returnToGameButton.width = 240;                         //
    returnToGameButton.height = 30;                         //

    bool collision = false; // bool used in GetCollisionRectangleRec() in collisions.cpp
    
    // Ball's directions
    Ball.right = false;
    Ball.left = false;
    Ball.up = false;
    Ball.down = false;

    // Speed
    Ball.speed = 5.0f;
    rectangles.speed = 5.0f;

    bool firstMoove = true;
    bool firstCollision = false;

    int counterPlayer1 = 0;
    int counterPlayer2 = 0;

    bool gameActive = false;

    int start = 0;

    // Main game loop
    while (!WindowShouldClose() && screen == Screen::game)    // Detect window close button or ESC key
    {       
        if (gameActive == false) // Only when the game restarts
        {
            start = rand() % 4 + 1;

            switch (start) // random int out of 4 numbers (1-4) that decides which corner the ball will go 
            {
            case 1: // Upper right
                Ball.up = true;
                Ball.right = true;
                break;
            case 2: // Lower right
                Ball.down = true;
                Ball.right = true;
                break;
            case 3: // Upper left     
                Ball.up = true;
                Ball.left = true;
                break;
            case 4: // Lower left     
                Ball.down = true;
                Ball.left = true;
                break;
            default:
                break;
            }
        }

        gameActive = true; // activate this bool in order to not get the random again until the next restart

        while (firstMoove == true)
        {
            // Draw

            BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangleRec(rectangle1, BLUE); // Player 1 rectangle
            DrawRectangleRec(rectangle2, RED); // Player 2 rectangle
            DrawRectangleRec(ball, WHITE); // Ball
            DrawText(TextFormat("% 8i", counterPlayer1), GetScreenWidth() / 2 - 300, 50, 50, BLUE); // Player 1 score
            DrawText(TextFormat("% 8i", counterPlayer2), GetScreenWidth() / 2, 50, 50, RED); // Player 2 score

            // Arrow indicating which side de ball is going
            if (Ball.right == true)
            {
                DrawRectangleRec(rightArrow, RED);
                DrawTriangle(Vector2{ 450,190 }, Vector2{ 450,210 }, Vector2{ 470,200 }, RED);
            }
            else if (Ball.left == true)
            {
                DrawRectangleRec(leftArrow, BLUE);
                DrawTriangle(Vector2{ 320,200 }, Vector2{ 340,210 }, Vector2{ 340,190 }, BLUE);
            }

            if (IsKeyDown(KEY_ENTER)) firstMoove = false; // Remove arrow and begin game after pressing ENTER

            EndDrawing();
        }

        // Draw again

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRectangleRec(rectangle1, BLUE); // Player 1 rectangle
        DrawRectangleRec(rectangle2, RED); // Player 2 rectangle
        DrawRectangleRec(ball, WHITE); // Ball
        DrawText(TextFormat("% 8i", counterPlayer1), GetScreenWidth() / 2 - 300, 50, 50, BLUE); // Player 1 score
        DrawText(TextFormat("% 8i", counterPlayer2), GetScreenWidth() / 2, 50, 50, RED); // Player 2 score

        EndDrawing();

        //----------------------------------------------------------------------------------

        // Players movement

        // Uppwards player 1 movement
        if (IsKeyDown(KEY_W))
        {
            rectangle1.y -= rectangles.speed;
            if (rectangle1.y <= 0)  rectangle1.y = 0;
        }
        // Downwards player 1 movement
        if (IsKeyDown(KEY_S))
        {
            rectangle1.y += rectangles.speed;
            if (rectangle1.y >= GetScreenHeight() - 62)  rectangle1.y = GetScreenHeight() - 62;
        }
        // Uppwards player 2 movement
        if (IsKeyDown(KEY_UP))
        {
            rectangle2.y -= rectangles.speed;
            if (rectangle2.y <= 0)  rectangle2.y = 0;
        }
        // Downwards player 2 movement
        if (IsKeyDown(KEY_DOWN))
        {
            rectangle2.y += rectangles.speed;
            if (rectangle2.y >= GetScreenHeight() - 62)  rectangle2.y = GetScreenHeight() - 62;
        }

        if (hits.leftWall == true) // Player 1 missed and ball hits left wall
        {
            counterPlayer2++; // Add 1 to the player's counter
           
            restartGame(hits, ball, rectangle1, rectangle2, Ball, rectangles, firstMoove, gameActive);
        }
        else if (hits.rightWall == true) // Player 2 missed and ball hits right wall
        {
            counterPlayer1++; // Add 1 to the player's counter         

            restartGame(hits, ball, rectangle1, rectangle2, Ball, rectangles, firstMoove, gameActive);
        }
        else collisions(ball, rectangle1, rectangle2, hits, collision, Ball); // If any collsion occures, trigger a bool in order to alwalys enter this else and call function to evaluate next collision   

        if (IsKeyPressed(KEY_SPACE)) // Pause
        {
            screen = Screen::pause; // Change the actual scene to trigger a loop where you can leave if you click in two positions or SPACE

            while (screen == Screen::pause)
            {
                BeginDrawing();

                if (CheckCollisionPointRec(GetMousePosition(), returnToMenuButton)) DrawText(FormatText("Return to Menu"), returnToMenuButton.x, returnToMenuButton.y, 30, BLUE);
                else  DrawText(FormatText("Return to Menu"), returnToMenuButton.x, returnToMenuButton.y, 30, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), returnToGameButton)) DrawText(FormatText("Return to game"), returnToGameButton.x, returnToGameButton.y, 30, BLUE);
                else  DrawText(FormatText("Return to game"), returnToGameButton.x, returnToGameButton.y, 30, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), returnToMenuButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::menu;
                if (CheckCollisionPointRec(GetMousePosition(), returnToGameButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::game;

                EndDrawing();

                if (IsKeyPressed(KEY_SPACE)) screen = Screen::game;
            }
        }   

        if (counterPlayer1 == 10 || counterPlayer2 == 10)
        {
            screen = Screen::finishedgame; // Change the actual scene to trigger a loop where you can leave if you press ESCAPE

            while (screen == Screen::finishedgame)
            {
                BeginDrawing();
                ClearBackground(BLACK);

                if (counterPlayer1 == 10)
                {
                    DrawText("Player 1 has won", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2, 40, BLUE);
                    DrawRectangleRec(rectangle1, BLUE); // Player 1 rectangle
                    DrawRectangleRec(rectangle2, RED); // Player 2 rectangle                    
                    DrawText(TextFormat("% 8i", counterPlayer1), GetScreenWidth() / 2 - 300, 50, 50, BLUE); // Player 1 score
                    DrawText(TextFormat("% 8i", counterPlayer2), GetScreenWidth() / 2, 50, 50, RED); // Player 2 score
                    DrawText("Press ENTER to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, BLUE);
                }
                else
                {
                    DrawText("Player 2 has won", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2, 40, RED);
                    DrawRectangleRec(rectangle1, BLUE); // Player 1 rectangle
                    DrawRectangleRec(rectangle2, RED); // Player 2 rectangle                    
                    DrawText(TextFormat("% 8i", counterPlayer1), GetScreenWidth() / 2 - 300, 50, 50, BLUE); // Player 1 score
                    DrawText(TextFormat("% 8i", counterPlayer2), GetScreenWidth() / 2, 50, 50, RED); // Player 2 score
                    DrawText("Press ENTER to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, RED);
                }

               
                EndDrawing();

                if (IsKeyPressed(KEY_ENTER))
                {
                    screen = Screen::menu;
                }
            }          
            restartGame(hits, ball, rectangle1, rectangle2, Ball, rectangles, firstMoove, gameActive);
        }
    } 

    screen = Screen::menu;
}