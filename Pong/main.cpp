#include "game.h"
#include "raylib.h"
#include "header.h"
#include "menu.h"
#include "credits.h"
#include "initGame.h"
#include "howToPlay.h"

/* Pierpaoli Matias
Practica Profesional 1: Desarrollo de Videojuegos 1
Pong*/

int main(void)
{
	Screen screen;	

	initGame(screen);

	while (!WindowShouldClose())
	{
		switch (screen)
		{
		case Screen::menu:
			menu(screen);
			break;
		case Screen::game:
			game(screen);
			break;
		case Screen::howToPlay:
			howToPlay(screen);
			break;
		case Screen::credits:
			credits(screen);
			break;
		case Screen::close:
			return 0;
		default:
			break;
		}
	}
	

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	
	return 0;

}