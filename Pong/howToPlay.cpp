#include "raylib.h"
#include "header.h"

void howToPlay(Screen& screen)
{	
	while (!WindowShouldClose() && screen == Screen::howToPlay)
	{	
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(FormatText("Rules:"), 15, 30, 40, BLUE);

		DrawText(FormatText("This simple tennis like game features two paddles and a ball."), 15, 110, 20, BLUE);
		DrawText(FormatText("Defeat your opponent by being the first one to gain 10 points."), 15, 140, 20, BLUE);
		DrawText(FormatText("A player gets a point once the opponent misses a ball and hits a wall."), 15, 170, 20, BLUE);
		DrawText(FormatText("Player	1 is on the left and controlles his paddle with w and s."), 15, 200, 20, BLUE);
		DrawText(FormatText("Player	2 is on the right and controlles his paddle with up and down arrow."), 15, 230, 20, BLUE);

		DrawText("Press ESC to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, BLUE);

		if (IsKeyDown(KEY_ESCAPE))
		{
			screen = Screen::menu;			
		}
		
		EndDrawing();
	}
	screen = Screen::menu;
}