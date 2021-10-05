#include "credits.h"
#include "raylib.h"
#include "header.h"

void credits(Screen& screen)
{
	while (!WindowShouldClose() && screen == Screen::credits)
	{
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(FormatText("Made by: Matias Pierpaoli"), GetScreenWidth() / 2 - 175, GetScreenHeight() / 2, 30, BLUE);
		DrawText("Press ESC to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, BLUE);

		EndDrawing();
	}

	screen = Screen::menu;



}