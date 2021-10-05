#pragma once
#include "raylib.h"

enum class Screen { menu, game, howToPlay, pause, credits, close, finishedgame };

struct Magnitudes
{
	int height;
	int width;
	float speed;
	bool up;
	bool down;
	bool left;
	bool right;
};

struct Hits // Types of hits (except players rectangles), used in main loop to determine ball direccion
{
	bool cieling = false;
	bool floor = false;
	bool leftWall = false;
	bool rightWall = false;

};

// Define function used in collisions.cpp
void collisions(Rectangle& ball, Rectangle& rectangle1, Rectangle& rectangle2, Hits& hits, bool& collision, Magnitudes& Ball);